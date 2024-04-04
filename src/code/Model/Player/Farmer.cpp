#include "Model/Player/Farmer.hpp"
#include <algorithm>
#include <cmath>

Farmer::Farmer() { this->type = FarmerType; }
Farmer::~Farmer() {}
Farmer *Farmer::clone() { return new Farmer(*this); }

int Farmer::countFarmWealth() {
	vector<FarmItem *> items;
	this->farm.getAllItem(items);

	int wealth = 0;
	for (const auto &itemPtr : items)
		wealth += itemPtr->getPrice();
	return wealth;
}

const int FarmerUntaxed = 13;
int Farmer::calculateTax() {
	int wealth = this->money + this->countInventoryWealth() + this->countFarmWealth();
	int taxed = wealth - FarmerUntaxed;
	int bracket = Player::getTaxBracket(taxed);
	return max((int)round((taxed * bracket) / 100.0), 0);
}
