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

int Player::countInventoryWealth() {
	vector<Heapify<Item> *> items;
	this->inventory.getAllItem(items);

	int wealth = 0;
	for (const auto &itemPtr : items)
		wealth += (*itemPtr)->getPrice();
	return wealth;
}