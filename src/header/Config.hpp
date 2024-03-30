#ifndef CLI_HPP
#define CLI_HPP

#include "Game.hpp"

class Config {
public:
	// TODO: Seperate state reader
	static void readConfig(
			string dir,
			GameContext &context
	);
};

#endif
