#include "Config.hpp"
#include "Item.hpp"
#include <fstream>

const string miscFilename = "misc.txt";
const string productItemFilename = "product.txt";
const string farmItemFilename = "plant.txt";
const string barnItemFilename = "animal.txt";
const string buildingFilename = "recipe.txt";
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
		ItemFactory<ProductItem> &productFactory,
		ItemFactory<FarmItem> &farmFactory,
		ItemFactory<BarnItem> &barnFactory,
		ItemFactory<BuildingItem> &buildingFactory
) {
	(void)players;

	ifstream miscFile;
	miscFile.open(dir + "/" + miscFilename);
	miscFile >> miscConfig;

	readItemConfigFile(dir + "/" + productItemFilename, productFactory);
	readItemConfigFile(dir + "/" + farmItemFilename, farmFactory);
	readItemConfigFile(dir + "/" + barnItemFilename, barnFactory);
	readItemConfigFile(dir + "/" + buildingFilename, buildingFactory);

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

		Heapify<Player> heapPlayer(NULL);
		if (type == "Petani") {
			PlayerFarmer farmer(username, weight, money);
			farmer.readProductFromStream(stateFile, productFactory);
			farmer.readFarmFromStream(stateFile, farmFactory);
			heapPlayer.set(&farmer);
		} else if (type == "Peternak") {
			PlayerBreeder breeder(username, weight, money);
			breeder.readProductFromStream(stateFile, productFactory);
			breeder.readBarnFromStream(stateFile, barnFactory);
			heapPlayer.set(&breeder);
		} else if (type == "Walikota") {
			PlayerMayor mayor(username, weight, money);
			mayor.readProductFromStream(stateFile, productFactory);
			heapPlayer.set(&mayor);
		} else {
			throw "Invalid player type";
		}
		players.addPlayer(heapPlayer);
	}
};
