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

PlayerFarmer *PlayerFarmer::clone() const { return new PlayerFarmer(*this); }
PlayerBreeder *PlayerBreeder::clone() const { return new PlayerBreeder(*this); }
PlayerMayor *PlayerMayor::clone() const { return new PlayerMayor(*this); }

string Player::getUsername() { return this->username; }
int Player::getWeight() { return this->weight; }
int Player::getMoney() { return this->money; }
PlayerType Player::getType() { return this->type; }

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
	auto begin = this->players.begin();
	auto end = begin + this->players.size();
	sort(begin, end, [](Heapify<Player> a, Heapify<Player> b) {
		return a->getUsername() < b->getUsername();
	});
}

void PlayerController::addPlayer(Heapify<Player> player) {
	this->players.push_back(player);
	this->rearrangePosition();
}

vector<Heapify<Player>> *PlayerController::getPlayers() {
	return &(this->players);
};
