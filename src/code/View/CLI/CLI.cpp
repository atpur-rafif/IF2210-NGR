#include "View/CLI/CLI.hpp"
#include "Exception/PlayerViewException.hpp"
#include "View/CLI/Player/BreederView.hpp"
#include "View/CLI/Player/FarmerView.hpp"
#include "View/CLI/Player/MayorView.hpp"
#include "View/Config/Config.hpp"

CLI::CLI() {
	this->view[FarmerType] = shared_ptr<PlayerView>{new FarmerView()};
	this->view[BreederType] = shared_ptr<PlayerView>{new BreederView()};
	this->view[MayorType] = shared_ptr<PlayerView>{new MayorView()};
};

shared_ptr<PlayerView> CLI::getView(PlayerType type) {
	if (this->view.find(type) == this->view.end())
		throw ViewNotImplementedPlayerViewException();
	return this->view[type];
};

void CLI::start() {
	Config::readConfig("./tmp/config", this->context);

	while (true) {
		shared_ptr<Player> current = this->context.players.getCurrentPlayer();
		shared_ptr<PlayerView> view = this->getView(current->type);
		view->start(*current);
		this->context.players.nextPlayer();
	}
}