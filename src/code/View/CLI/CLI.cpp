#include "View/CLI/CLI.hpp"
#include "View/Config/Config.hpp"

CLI::CLI(){};

void CLI::start() {
	Config::readConfig("./tmp/config", this->context);
}

void CLI::playerTurnCommand(string command) {
	(void)command;
};

void CLI::farmerTurnCommand(string command) {
	(void)command;
};

void CLI::breederTurnCommand(string command) {
	(void)command;
};

void CLI::mayorTurnCommand(string command) {
	(void)command;
};
