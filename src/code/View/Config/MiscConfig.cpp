#include "View/Config/MiscConfig.hpp"

MiscConfig::MiscConfig(){};
int MiscConfig::getTargetMoney() { return this->targetMoney; };
int MiscConfig::getTargetWeight() { return this->targetWeight; };

int MiscConfig::getInventoryWidth() { return this->inventoryWidth; };
int MiscConfig::getBarnWidth() { return this->barnWidth; };
int MiscConfig::getFarmWidth() { return this->farmWidth; };

int MiscConfig::getInventoryHeight() { return this->inventoryHeight; };
int MiscConfig::getBarnHeight() { return this->barnHeight; };
int MiscConfig::getFarmHeight() { return this->farmHeight; };

istream &operator>>(istream &inputStream, MiscConfig &config) {
	inputStream >> config.targetMoney;
	inputStream >> config.targetWeight;

	inputStream >> config.inventoryHeight;
	inputStream >> config.inventoryWidth;

	inputStream >> config.farmHeight;
	inputStream >> config.farmWidth;

	inputStream >> config.barnHeight;
	inputStream >> config.barnWidth;

	return inputStream;
};
