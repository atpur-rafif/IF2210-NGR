#include "View/Config/Config.hpp"
#include "Exception/ConfigException.hpp"
#include "Model/Item.hpp"
#include "Model/Item/BarnItem.hpp"
#include "Model/Item/BuildingItem.hpp"
#include "Model/Item/FarmItem.hpp"
#include "Model/Item/ProductItem.hpp"
#include <filesystem>
#include <fstream>
#include <ostream>
#include <sstream>
#include <sys/stat.h>

const string miscFilename = "misc.txt";
const string productItemFilename = "product.txt";
const string farmItemFilename = "plant.txt";
const string barnItemFilename = "animal.txt";
const string buildingFilename = "recipe.txt";
const string stateFilename = "state.txt";

string Config::defaultState =
		"3"
		"Petani1 Petani 50 40 0 0"
		"Peternak1 Peternak 50 40 0 0"
		"Walikota Walikota 50 40 0";

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
	miscFile >> context.getMiscConfig();

	readItemConfigFileMacro(ProductItem, dir, productItemFilename, context.getItemFactory());
	readItemConfigFileMacro(FarmItem, dir, farmItemFilename, context.getItemFactory());
	readItemConfigFileMacro(BarnItem, dir, barnItemFilename, context.getItemFactory());
	readItemConfigFileMacro(BuildingItem, dir, buildingFilename, context.getItemFactory());
};

void Config::readState(string dir, GameContext &context) {
	if (!filesystem::is_directory(dir))
		throw InvalidDirectoryConfigException();

	ifstream stateFile;
	stateFile.open(dir + "/" + stateFilename);
	int playerCount;
	stateFile >> playerCount;
	while (playerCount--) {
		shared_ptr<Player> player = context.getPlayerController().readPlayerFromStream(stateFile);
		context.getPlayerController().addPlayer(player);
	}
}

void Config::readDefaultState(GameContext &context) {
	istringstream stateStream(Config::defaultState);
	int playerCount;
	stateStream >> playerCount;
	while (playerCount--) {
		shared_ptr<Player> player = context.getPlayerController().readPlayerFromStream(stateStream);
		context.getPlayerController().addPlayer(player);
	}
}

void Config::writeState(string dir, GameContext &context) {
	ofstream outputStream;
	outputStream.open(dir + "/" + stateFilename);
	auto players = context.getPlayerController().getPlayers();
	outputStream << players.size() << endl;
	for (auto player : players) {
		outputStream << player->getUsername() << ' ';
		outputStream << Player::playerTypeToString(player->getType()) << ' ';
		outputStream << player->getWeight() << ' ';
		outputStream << player->getMoney() << endl;
		player->writeInventory(outputStream);
		player->writeSpecializedConfig(outputStream);
	}
};
