#ifndef VIEW_CONFIG_HPP
#define VIEW_CONFIG_HPP

#include "Controller/GameContext.hpp"
#include <string>

using namespace std;
class Config {
public:
	static void readConfig(
			string dir,
			GameContext &context
	);

	static void readState(
			string dir,
			GameContext &context
	);
};

#endif
