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
static void readItemConfigFile(string fullpath, ItemFactory<T> &controller) {
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
		ItemFactory<InventoryItem> &inventoryFactory,
		ItemFactory<FarmItem> &farmFactory,
		ItemFactory<BarnItem> &barnFactory,
		ItemFactory<RecipeItem> &recipeFactory
) {
	(void)players;

	ifstream miscFile;
	miscFile.open(dir + "/" + miscFilename);
	miscFile >> miscConfig;

	readItemConfigFile(dir + "/" + inventoryItemFilename, inventoryFactory);
	readItemConfigFile(dir + "/" + farmItemFilename, farmFactory);
	readItemConfigFile(dir + "/" + barnItemFilename, barnFactory);
	readItemConfigFile(dir + "/" + recipeFilename, recipeFactory);

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
			farmer.readInventoryFromStream(stateFile, inventoryFactory);
			farmer.readFarmFromStream(stateFile, farmFactory);
			players.addFarmer(farmer);
		} else if (type == "Peternak") {
			PlayerBreeder breeder(username, weight, money);
			breeder.readInventoryFromStream(stateFile, inventoryFactory);
			breeder.readBarnFromStream(stateFile, barnFactory);
			players.addBreeder(breeder);
		} else if (type == "Walikota") {
			PlayerMayor mayor(username, weight, money);
			mayor.readInventoryFromStream(stateFile, inventoryFactory);
			players.addMayor(mayor);
		}
	}
};
