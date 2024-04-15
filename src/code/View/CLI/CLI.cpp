#include "View/CLI/CLI.hpp"
#include "Exception/CLIException.hpp"
#include "View/CLI/Player/BreederView.hpp"
#include "View/CLI/Player/FarmerView.hpp"
#include "View/CLI/Player/MayorView.hpp"
#include "View/Config/Config.hpp"

int CLI::promptOption(int from, int to, string message) {
	function<int(string)> fn = [=](string input) {
		int result = atoi(input.c_str());
		if (from <= result && result <= to)
			return result;
		else throw PromptException("Pilihan tidak valid");
	};
	return CLI::prompt(message, fn);
};

CLI::CLI() {
	this->view[FarmerType] = shared_ptr<PlayerView>{new FarmerView()};
	this->view[BreederType] = shared_ptr<PlayerView>{new BreederView()};
	this->view[MayorType] = shared_ptr<PlayerView>{new MayorView()};
};

shared_ptr<PlayerView> CLI::getView(PlayerType type) {
	if (this->view.find(type) == this->view.end())
		throw GameException("Unimplemented view");
	return this->view[type];
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
	cout << "State option:" << endl;
	cout << "1. Use default state" << endl;
	cout << "2. Read from file" << endl;
	cout << "> ";

	string prompt;
	while (true) {
		cin >> prompt;
		if (prompt == "1") {
			Config::readDefaultState(this->context);
			cout << "Using default state" << endl;
			break;
		} else if (prompt == "2") {
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
			break;
		} else {
			cout << "Invalid option" << endl;
		}
	}
}

void CLI::start() {
	// this->config();
	// this->state();

	Config::readConfig("tmp/config", this->context);
	Config::readState("tmp/config", this->context);
	while (true) {
		shared_ptr<Player> current = this->context.getPlayerController().getCurrentPlayer();
		shared_ptr<PlayerView> view = this->getView(current->getType());
		view->start(*current);
		this->context.getPlayerController().nextPlayer();
	}
}
