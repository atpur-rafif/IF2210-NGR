#include "Player.hpp"
#include <algorithm>

// clang-format off

Player::Player(string username, PlayerType type, int weight, int money):
	username(username),
	type(type),
	weight(weight),
	money(money)
{};

PlayerFarmer::PlayerFarmer(string username, int weight, int money): 
	Player(username, Farmer, weight, money){};

PlayerBreeder::PlayerBreeder(string username, int weight, int money): 
	Player(username, Breeder, weight, money){};

PlayerMayor::PlayerMayor(string username, int weight, int money): 
	Player(username, Mayor, weight, money){};

// clang-format on

Player::~Player(){};
PlayerFarmer::~PlayerFarmer() {}
PlayerBreeder::~PlayerBreeder() {}
PlayerMayor::~PlayerMayor() {}

string Player::getUsername() { return this->username; }
int Player::getWeight() { return this->weight; }
int Player::getMoney() { return this->money; }

void Player::readProductFromStream(istream &inputStream, ItemFactory<ProductItem> productFactory) {
	int productCount;
	inputStream >> productCount;
	while (productCount--) {
		string name;
		inputStream >> name;
		int id = productFactory.getIdByName(name);
		ProductItem item = productFactory.createItemById(id);
		this->inventory.addItem(item);
	}
}

void PlayerFarmer::readFarmFromStream(istream &inputStream, ItemFactory<FarmItem> farmFactory) {
	int farmCount;
	inputStream >> farmCount;
	while (farmCount--) {
		string location;
		inputStream >> location;

		string name;
		inputStream >> name;

		int id = farmFactory.getIdByName(name);
		FarmItem item = farmFactory.createItemById(id);

		int age;
		inputStream >> age;
		item.setAge(age);

		this->farm.addItem(item);
	}
};

void PlayerBreeder::readBarnFromStream(istream &inputStream, ItemFactory<BarnItem> barnFactory) {
	int barnCount;
	inputStream >> barnCount;
	while (barnCount--) {
		string location;
		inputStream >> location;

		string name;
		inputStream >> name;

		int id = barnFactory.getIdByName(name);
		BarnItem item = barnFactory.createItemById(id);

		int age;
		inputStream >> age;
		item.setWeight(age);

		this->barn.addItem(item);
	}
};

void PlayerController::rearrangePosition() {
	this->players.clear();
	for (auto &farmer : this->farmer) this->players.push_back(&farmer);
	for (auto &breeder : this->breeder) this->players.push_back(&breeder);
	for (auto &mayor : this->mayor) this->players.push_back(&mayor);

	auto begin = this->players.begin();
	auto end = begin + this->players.size();
	(void)end;
	sort(begin, end, [](Player *a, Player *b) {
		return a->getUsername() < b->getUsername();
	});
}

void PlayerController::addFarmer(PlayerFarmer farmer) {
	this->farmer.push_back(farmer);
	this->rearrangePosition();
}

void PlayerController::addBreeder(PlayerBreeder breeder) {
	this->breeder.push_back(breeder);
	this->rearrangePosition();
}

void PlayerController::addMayor(PlayerMayor mayor) {
	this->mayor.push_back(mayor);
	this->rearrangePosition();
}

vector<Player *> *PlayerController::getPlayers() {
	return &(this->players);
};
