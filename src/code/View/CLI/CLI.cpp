#include "View/CLI/CLI.hpp"
#include "Exception/PlayerViewException.hpp"
#include "View/CLI/Player/BreederView.hpp"
#include "View/CLI/Player/FarmerView.hpp"
#include "View/CLI/Player/MayorView.hpp"
#include "View/Config/Config.hpp"

CLI::CLI() {
	this->view[FarmerType] = Heapify(FarmerView());
	this->view[BreederType] = Heapify(BreederView());
	this->view[MayorType] = Heapify(MayorView());
};

PlayerView &CLI::getView(PlayerType type) {
	if (this->view.find(type) == this->view.end())
		throw ViewNotImplementedPlayerViewException();
	return this->view.at(type).get();
};

void CLI::config() {
	while (true) {
		string dir;
		cout << "Config directory: ";
		cin >> dir;
		try {
			Config::readConfig(dir, this->context);
			cout << "Config loaded" << endl;
			break;
		} catch (const std::exception &e) {
			cout << e.what() << endl;
		}
	}
}

void CLI::state() {
	while (true) {
		string dir;
		cout << "State directory: ";
		cin >> dir;
		try {
			Config::readState(dir, this->context);
			cout << "State loaded" << endl;
			break;
		} catch (const std::exception &e) {
			cout << e.what() << endl;
		}
	}
}

void CLI::start() {
	this->config();
	this->state();

	while (true) {
		Player &current = this->context.players.getCurrentPlayer();
		PlayerView &view = this->getView(current.type);
		view.start(current);
		this->context.players.nextPlayer();
	}
}
