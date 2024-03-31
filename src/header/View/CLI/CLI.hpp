#ifndef CLI_HPP
#define CLI_HPP

#include "Controller/GameContext.hpp"

class CLI {
private:
	GameContext context;

public:
	CLI();

	void start();

	void configPrompt();
	void statePrompt();

	void turnPrompt();

	void playerTurnCommand(string command);
	void farmerTurnCommand(string command);
	void breederTurnCommand(string command);
	void mayorTurnCommand(string command);
};

#endif
