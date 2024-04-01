#ifndef VIEW_CLI_HPP
#define VIEW_CLI_HPP

#include "Controller/GameContext.hpp"
#include "Model/Player.hpp"
#include "View/CLI/PlayerView.hpp"

class CLI {
private:
	GameContext context;
	map<PlayerType, Heapify<PlayerView>> view;

public:
	CLI();
	void start();
	PlayerView &getView(PlayerType type);
};

#endif
