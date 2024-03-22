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
static void readVectorConfigFile(string fullpath, vector<T> &vector) {
	ifstream fileStream;
	fileStream.open(fullpath);
	cout << fullpath << endl;
	while (fileStream.peek() != EOF) {
		T element;
		fileStream >> element >> ws;
		vector.push_back(element);
	}
}

void Config::readConfig(
		string dir,
		MiscConfig &miscConfig,
		vector<Player *> &players,
		vector<InventoryItem> &inventoryItems,
		vector<FarmItem> &farmItems,
		vector<BarnItem> &barnItems,
		vector<RecipeItem> &recipes
) {
	(void)players;
	(void)recipes;

	ifstream miscFile;
	miscFile.open(dir + "/" + miscFilename);
	miscFile >> miscConfig;

	readVectorConfigFile(dir + "/" + inventoryItemFilename, inventoryItems);
	readVectorConfigFile(dir + "/" + farmItemFilename, farmItems);
	readVectorConfigFile(dir + "/" + barnItemFilename, barnItems);
	readVectorConfigFile(dir + "/" + recipeFilename, recipes);
};
