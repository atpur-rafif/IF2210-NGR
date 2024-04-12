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

void CLI::start() {
	Config::readConfig("./tmp/config", this->context);

	while (true) {
		Player &current = this->context.players.getCurrentPlayer();
		PlayerView &view = this->getView(current.type);
		view.start(current);
		this->context.players.nextPlayer();
	}
}