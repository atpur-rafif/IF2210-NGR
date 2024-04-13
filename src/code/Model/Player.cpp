#include "Model/Player.hpp"

Player::Player() {}
Player::~Player() {}

int Player::getTaxBracket(int taxed) {
	if (taxed <= 6) return 5;
	else if (taxed <= 25) return 15;
	else if (taxed <= 50) return 25;
	else if (taxed <= 500) return 30;
	else return 35;
};

string Player::playerTypeToString(int type){
	vector<string> typeString{"Petani","Peternak","Walikota"};
	return typeString[type];
}

int Player::countInventoryWealth() {
	vector<shared_ptr<Item> *> items = this->inventory.getAllItem();

	int wealth = 0;
	for (const auto &itemPtr : items)
		wealth += (*itemPtr)->getPrice();
	return wealth;
}