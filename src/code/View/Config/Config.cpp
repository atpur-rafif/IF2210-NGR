#include "View/Config/Config.hpp"
#include "Model/Item.hpp"
#include "Model/Item/BarnItem.hpp"
#include "Model/Item/BuildingItem.hpp"
#include "Model/Item/FarmItem.hpp"
#include "Model/Item/ProductItem.hpp"
#include <fstream>

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
	ifstream miscFile;
	miscFile.open(dir + "/" + miscFilename);
	miscFile >> context.miscConfig;

	readItemConfigFileMacro(ProductItem, dir, productItemFilename, context.itemFactory);
	readItemConfigFileMacro(FarmItem, dir, farmItemFilename, context.itemFactory);
	readItemConfigFileMacro(BarnItem, dir, barnItemFilename, context.itemFactory);
	readItemConfigFileMacro(BuildingItem, dir, buildingFilename, context.itemFactory);

	ifstream stateFile;
	stateFile.open(dir + "/" + stateFilename);
	int playerCount;
	stateFile >> playerCount;
	while (playerCount--) {
		shared_ptr<Player> player = context.players.readPlayerFromStream(stateFile);
		context.players.addPlayer(player);
	}
	context.players.rearrangePosition();
};
