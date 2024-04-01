#ifndef VIEW_CLI_PLAYERVIEW_HPP
#define VIEW_CLI_PLAYERVIEW_HPP

#include "Model/Player.hpp"

class PlayerView {
public:
	virtual ~PlayerView();
	virtual PlayerView *clone() = 0;
	void start(Player &player);
	void runPlayerCommand(Player &player, string command);
	virtual void runSpecializedPlayerCommand(Player &player, string command) = 0;
	void printInventory(Player &player);
	void eat(Player &player);
};

#endif
