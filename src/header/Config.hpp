#ifndef CLI_HPP
#define CLI_HPP

#include "GameContext.hpp"
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
