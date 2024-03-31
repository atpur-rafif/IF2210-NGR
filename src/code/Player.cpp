#include "Player.hpp"
#include "GameContext.hpp"

Player::Player() {}
Farmer::Farmer() { this->type = FarmerType; }
Breeder::Breeder() { this->type = BreederType; }
Mayor::Mayor() { this->type = MayorType; }

Player::~Player() {}
Farmer::~Farmer() {}
Breeder::~Breeder() {}
Mayor::~Mayor() {}

Player *Player::clone() { return new Player(*this); }
Farmer *Farmer::clone() { return new Farmer(*this); }
Breeder *Breeder::clone() { return new Breeder(*this); }
Mayor *Mayor::clone() { return new Mayor(*this); }

istream &operator>>(istream &inputStream, Heapify<Player> &player) {
	int weight, money;
	string username, type;
	inputStream >> username >> type >> weight >> money;

	GameContext &context = player->getContext();

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

	player.set(newPlayer);
	return inputStream;
};
