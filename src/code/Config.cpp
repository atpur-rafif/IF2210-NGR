#include "Config.hpp"
#include "Item.hpp"
#include <fstream>

const string miscFilename = "misc.txt";
const string productItemFilename = "product.txt";
const string farmItemFilename = "plant.txt";
const string barnItemFilename = "animal.txt";
const string buildingFilename = "recipe.txt";
// const string stateFilename = "state.txt";

#define readItemConfigFileMacro(type, dir, filename, itemFactory) \
	{                                                               \
		ifstream fileStream;                                          \
		fileStream.open(dir + "/" + filename);                        \
		while (fileStream.peek() != EOF) {                            \
			type element;                                               \
			fileStream >> element >> ws;                                \
			itemFactory.addItem(element);                               \
		}                                                             \
	}

void Config::readConfig(
		string dir,
		MiscConfig &miscConfig,
		PlayerController &players,
		ItemFactory &itemFactory
) {
	(void)players;

	ifstream miscFile;
	miscFile.open(dir + "/" + miscFilename);
	miscFile >> miscConfig;

	readItemConfigFileMacro(ProductItem, dir, productItemFilename, itemFactory);
	readItemConfigFileMacro(FarmItem, dir, farmItemFilename, itemFactory);
	readItemConfigFileMacro(BarnItem, dir, barnItemFilename, itemFactory);
	readItemConfigFileMacro(BuildingItem, dir, buildingFilename, itemFactory);
};
