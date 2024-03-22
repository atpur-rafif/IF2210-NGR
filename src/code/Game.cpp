#include "Game.hpp"

Config::Config(){};
int Config::getTargetMoney() { return this->targetMoney; };
int Config::getTargetWeight() { return this->targetWeight; };
pair<int, int> Config::getInventorySize() { return this->inventorySize; };
pair<int, int> Config::getBarnSize() { return this->barnSize; };
pair<int, int> Config::getFarmSize() { return this->farmSize; };

istream &operator>>(istream &inputStream, Config &config) {
	inputStream >> config.targetMoney;
	inputStream >> config.targetWeight;

	inputStream >> config.inventorySize.first;
	inputStream >> config.inventorySize.second;

	inputStream >> config.farmSize.first;
	inputStream >> config.farmSize.second;

	inputStream >> config.barnSize.first;
	inputStream >> config.barnSize.second;

	return inputStream;
};
