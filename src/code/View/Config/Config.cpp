#include "View/Config/Config.hpp"
#include "Exception/ConfigException.hpp"
#include "Model/Item.hpp"
#include "Model/Item/BarnItem.hpp"
#include "Model/Item/BuildingItem.hpp"
#include "Model/Item/FarmItem.hpp"
#include "Model/Item/ProductItem.hpp"
#include <filesystem>
#include <fstream>
#include <sys/stat.h>

const string miscFilename = "misc.txt";
const string productItemFilename = "product.txt";
const string farmItemFilename = "plant.txt";
const string barnItemFilename = "animal.txt";
const string buildingFilename = "recipe.txt";
const string stateFilename = "state.txt";

#define readItemConfigFileMacro(type, dir, filename, itemFactory) \
	{                                                               \
		ifstream fileStream;                                          \
		fileStream.open(dir + "/" + filename);                        \
		if (!fileStream)                                              \
			throw FileNotFoundConfigException(filename);                \
		while (fileStream.peek() != EOF) {                            \
			type element;                                               \
			fileStream >> element >> ws;                                \
			itemFactory.addTemplateItem(element);                       \
		}                                                             \
	}

void Config::readConfig(
		string dir,
		GameContext &context
) {
	if (!filesystem::is_directory(dir))
		throw InvalidDirectoryConfigException();

	ifstream miscFile;
	miscFile.open(dir + "/" + miscFilename);
	miscFile >> context.miscConfig;

	readItemConfigFileMacro(ProductItem, dir, productItemFilename, context.itemFactory);
	readItemConfigFileMacro(FarmItem, dir, farmItemFilename, context.itemFactory);
	readItemConfigFileMacro(BarnItem, dir, barnItemFilename, context.itemFactory);
	readItemConfigFileMacro(BuildingItem, dir, buildingFilename, context.itemFactory);
};

void Config::readState(string dir, GameContext &context) {
	if (!filesystem::is_directory(dir))
		throw InvalidDirectoryConfigException();

	ifstream stateFile;
	stateFile.open(dir + "/" + stateFilename);
	int playerCount;
	stateFile >> playerCount;
	while (playerCount--) {
		Heapify<Player> player = context.players.readPlayerFromStream(stateFile);
		context.players.addPlayer(player);
	}
	context.players.rearrangePosition();
}
