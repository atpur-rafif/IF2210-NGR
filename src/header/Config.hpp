#ifndef CLI_HPP
#define CLI_HPP

#include "ItemFactory.hpp"
#include "MiscConfig.hpp"
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
