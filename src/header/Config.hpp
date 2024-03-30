#ifndef CLI_HPP
#define CLI_HPP

#include "Game.hpp"
#include "ItemFactory.hpp"
#include "PlayerController.hpp"

class Config {
public:
	// TODO: seperate state reader
	static void readConfig(
			string dir,
			MiscConfig &miscConfig,
			PlayerController &players,
			ItemFactory &itemFactory
	);
};

#endif
