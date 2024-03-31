#include "Player.hpp"
#include <cmath>
#include <vector>

Player::Player() {}
Farmer::Farmer() { this->type = FarmerType; }
Breeder::Breeder() { this->type = BreederType; }
Mayor::Mayor() { this->type = MayorType; }

Player::~Player() {}
Farmer::~Farmer() {}
Breeder::~Breeder() {}
Mayor::~Mayor() {}

Farmer *Farmer::clone() { return new Farmer(*this); }
Breeder *Breeder::clone() { return new Breeder(*this); }
Mayor *Mayor::clone() { return new Mayor(*this); }

int Player::countInventoryWealth() {
	vector<Heapify<Item> *> items;
	this->inventory.getAllItem(items);

	int wealth = 0;
	for (const auto &itemPtr : items)
		wealth += (*itemPtr)->getPrice();
	return wealth;
}

int Farmer::countFarmWealth() {
	vector<FarmItem *> items;
	this->farm.getAllItem(items);

	int wealth = 0;
	for (const auto &itemPtr : items)
		wealth += itemPtr->getPrice();
	return wealth;
}

int Breeder::countBarnWealth() {
	vector<BarnItem *> items;
	this->barn.getAllItem(items);

	int wealth = 0;
	for (const auto &itemPtr : items)
		wealth += itemPtr->getPrice();
	return wealth;
}

static int getTaxBracket(int taxed) {
	if (taxed <= 6) return 5;
	else if (taxed <= 25) return 15;
	else if (taxed <= 50) return 25;
	else if (taxed <= 500) return 30;
	else return 35;
};

const int FarmerUntaxed = 13;
int Farmer::calculateTax() {
	int wealth = this->money + this->countInventoryWealth() + this->countFarmWealth();
	int taxed = wealth - FarmerUntaxed;
	int bracket = getTaxBracket(taxed);
	return round((taxed * bracket) / 100.0);
}

const int BreederUntaxed = 11;
int Breeder::calculateTax() {
	int wealth = this->money + this->countInventoryWealth() + this->countBarnWealth();
	int taxed = wealth - BreederUntaxed;
	int bracket = getTaxBracket(taxed);
	return round((taxed * bracket) / 100.0);
}

int Mayor::calculateTax() {
	return 0;
}
