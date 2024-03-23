#include "Config.hpp"
#include "Item.hpp"
#include "filesystem"
#include <filesystem>

const string miscFilename = "misc.txt";
const string inventoryItemFilename = "product.txt";
const string farmItemFilename = "plant.txt";
const string barnItemFilename = "animal.txt";
const string recipeFilename = "recipe.txt";

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
		vector<Player *> &players,
		ItemController<InventoryItem> &inventoryItems,
		ItemController<FarmItem> &farmItems,
		ItemController<BarnItem> &barnItems,
		ItemController<RecipeItem> &recipeItems

) {
	(void)players;
	(void)recipeItems;

	ifstream miscFile;
	miscFile.open(dir + "/" + miscFilename);
	miscFile >> miscConfig;

	readItemConfigFile(dir + "/" + inventoryItemFilename, inventoryItems);
	readItemConfigFile(dir + "/" + farmItemFilename, farmItems);
	readItemConfigFile(dir + "/" + barnItemFilename, barnItems);
	readItemConfigFile(dir + "/" + recipeFilename, recipeItems);
};
