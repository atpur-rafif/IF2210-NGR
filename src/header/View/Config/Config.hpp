#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Controller/GameContext.hpp"
#include <string>

using namespace std;
class Config {
public:
	// TODO: Seperate state reader
	static void readConfig(
			string dir,
			GameContext &context
	);
};

#endif
