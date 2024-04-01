#include "Controller/PlayerController.hpp"
#include "Controller/GameContext.hpp"
#include "Model/Player/Breeder.hpp"
#include "Model/Player/Farmer.hpp"
#include "Model/Player/Mayor.hpp"
#include <algorithm>

PlayerController::PlayerController() {
	this->currentPlayerIndex = 0;
}

Player &PlayerController::getCurrentPlayer() {
	return *this->ordered.at(this->currentPlayerIndex);
};

void PlayerController::rearrangePosition() {
	int size = this->players.size();
	this->ordered.resize(size);
	for (int i = 0; i < size; ++i)
		this->ordered[i] = this->players[i].getRaw();

	auto begin = this->ordered.begin();
	auto end = begin + this->ordered.size();

	sort(begin, end, [](Player *a, Player *b) {
		return a->username < b->username;
	});
}

void PlayerController::addPlayer(Heapify<Player> &player) {
	this->players.push_back(player);
	this->rearrangePosition();
};

vector<Player *> *PlayerController::getPlayers() {
	return &(this->ordered);
}

Heapify<Player> PlayerController::readPlayerFromStream(istream &inputStream) {
	int weight, money;
	string username, type;
	inputStream >> username >> type >> weight >> money;

	GameContext &context = this->getContext();

	Player *newPlayer;
	if (type == "Petani") newPlayer = new Farmer();
	else if (type == "Peternak") newPlayer = new Breeder();
	else if (type == "Walikota") newPlayer = new Mayor();
	else throw "Invalid player type";

	newPlayer->username = username;
	newPlayer->weight = weight;
	newPlayer->money = money;
	auto inventorySize = context.miscConfig.getInventorySize();
	newPlayer->inventory = HeapifyStorage<Item>(inventorySize.first, inventorySize.second);

	int inventoryCount;
	inputStream >> inventoryCount;
	while (inventoryCount--) {
		string name;
		inputStream >> name;
		string code = context.itemFactory.getCodeByName(name);
		Heapify<Item> item = context.itemFactory.createBaseItem(code);
		newPlayer->inventory.addItem(item);
	}

	if (newPlayer->type == FarmerType) {
		Farmer *farmer = dynamic_cast<Farmer *>(newPlayer);

		auto farmSize = context.miscConfig.getFarmSize();
		farmer->farm = Storage<FarmItem>(farmSize.first, farmSize.second);
		int farmCount;
		inputStream >> farmCount;
		while (farmCount--) {
			int age;
			string location, name;
			inputStream >> location >> name >> age;
			string code = context.itemFactory.getCodeByName(name);
			FarmItem item;
			context.itemFactory.createItem(code, item);
			farmer->farm.setItem(location, item);
		}
	} else if (newPlayer->type == BreederType) {
		Breeder *breeder = dynamic_cast<Breeder *>(newPlayer);

		auto barnSize = context.miscConfig.getBarnSize();
		breeder->barn = Storage<BarnItem>(barnSize.first, barnSize.second);
		int farmCount;
		inputStream >> farmCount;
		while (farmCount--) {
			int age;
			string location, name;
			inputStream >> location >> name >> age;
			string code = context.itemFactory.getCodeByName(name);
			BarnItem item;
			context.itemFactory.createItem(code, item);
			breeder->barn.setItem(location, item);
		}
	}

	Heapify<Player> heap = Heapify(newPlayer);
	delete newPlayer;

	return heap;
};
