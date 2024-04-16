#ifndef VIEW_CLI_PLAYERVIEW_HPP
#define VIEW_CLI_PLAYERVIEW_HPP

#include "Controller/GameContext.hpp"
#include "Exception/CLIException.hpp"
#include "Exception/StorageException.hpp"
#include "Model/Player.hpp"
#include "Model/Player/Farmer.hpp"
#include <exception>

class PlayerView {
public:
	virtual ~PlayerView();
	virtual PlayerView *clone() = 0;

	void start(Player &player);
	void runPlayerCommand(Player &player, string command);
	virtual void runSpecializedPlayerCommand(Player &player, string command) = 0;
	static void printInventory(Player &player);
	static void eat(Player &player);
	static void save(Player &player);
};

#endif
