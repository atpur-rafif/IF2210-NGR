#include "Config.hpp"
#include "Item.hpp"
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
			itemFactory.addItem(element);                               \
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
		Player player;
		stateFile >> player;
		player.setContext(context);
		player.readInventoryFromStream(stateFile);

		if (player.getType() == Farmer) {
			FarmerSpecialization farmer;
			player.specialize(farmer);
		} else if (player.getType() == Breeder) {
			BreederSpecialization breeder;
			player.specialize(breeder);
		} else if (player.getType() == Mayor) {
			MayorSpecialization mayor;
			player.specialize(mayor);
		} else {
			throw "Player specialization undefined";
		}

		player.getSpecialization().readSpecializationFromStream(stateFile);
		context.players.addPlayer(player);
	}
};
