#ifndef VIEW_CLI_HPP
#define VIEW_CLI_HPP

#include "Controller/GameContext.hpp"
#include "Model/Player.hpp"
#include "View/CLI/PlayerView.hpp"

class CLI {
private:
	GameContext context;
	map<PlayerType, shared_ptr<PlayerView>> view;

public:
	CLI();
	void start();
	shared_ptr<PlayerView> getView(PlayerType type);
};

#endif
