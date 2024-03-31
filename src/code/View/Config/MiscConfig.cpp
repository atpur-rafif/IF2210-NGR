#include "View/Config/MiscConfig.hpp"

MiscConfig::MiscConfig(){};
int MiscConfig::getTargetMoney() { return this->targetMoney; };
int MiscConfig::getTargetWeight() { return this->targetWeight; };
pair<int, int> MiscConfig::getInventorySize() { return this->inventorySize; };
pair<int, int> MiscConfig::getBarnSize() { return this->barnSize; };
pair<int, int> MiscConfig::getFarmSize() { return this->farmSize; };

istream &operator>>(istream &inputStream, MiscConfig &config) {
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
