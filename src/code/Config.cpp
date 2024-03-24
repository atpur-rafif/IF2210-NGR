#include "Config.hpp"
#include "Item.hpp"
#include "filesystem"
#include <filesystem>

const string miscFilename = "misc.txt";
const string inventoryItemFilename = "product.txt";
const string farmItemFilename = "plant.txt";
const string barnItemFilename = "animal.txt";
const string recipeFilename = "recipe.txt";
const string stateFilename = "state.txt";

template <class T>
static void readItemConfigFile(string fullpath, ItemController<T> &controller) {
	ifstream fileStream;
	fileStream.open(fullpath);
	cout << fullpath << endl;
	while (fileStream.peek() != EOF) {
		T element;
		fileStream >> element >> ws;
		controller.addItem(element);
	}
}

void Config::readConfig(
		string dir,
		MiscConfig &miscConfig,
		PlayerController &players,
		ItemController<InventoryItem> &inventoryItems,
		ItemController<FarmItem> &farmItems,
		ItemController<BarnItem> &barnItems,
		ItemController<RecipeItem> &recipeItems
) {
	(void)players;

	ifstream miscFile;
	miscFile.open(dir + "/" + miscFilename);
	miscFile >> miscConfig;

	readItemConfigFile(dir + "/" + inventoryItemFilename, inventoryItems);
	readItemConfigFile(dir + "/" + farmItemFilename, farmItems);
	readItemConfigFile(dir + "/" + barnItemFilename, barnItems);
	readItemConfigFile(dir + "/" + recipeFilename, recipeItems);

	ifstream stateFile;
	stateFile.open(dir + "/" + stateFilename);
	int playerCount;
	stateFile >> playerCount;
	// TODO: Seperate reader for every player type
	while (playerCount--) {
		string username;
		string type;
		int weight;
		int money;
		stateFile >> username >> type >> weight >> money;
		if (type == "Petani") {
			PlayerFarmer farmer(username, weight, money);
			farmer.readInventoryFromStream(stateFile, inventoryItems);
			farmer.readFarmFromStream(stateFile, farmItems);
			players.addFarmer(farmer);
		} else if (type == "Peternak") {
			PlayerBreeder breeder(username, weight, money);
			breeder.readInventoryFromStream(stateFile, inventoryItems);
			breeder.readBarnFromStream(stateFile, barnItems);
			players.addBreeder(breeder);
		} else if (type == "Walikota") {
			PlayerMayor mayor(username, weight, money);
			mayor.readInventoryFromStream(stateFile, inventoryItems);
			players.addMayor(mayor);
		}
	}
};
