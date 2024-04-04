#include "Model/Player/Breeder.hpp"
#include <cmath>

Breeder::Breeder() { this->type = BreederType; }
Breeder::~Breeder() {}
Breeder *Breeder::clone() { return new Breeder(*this); }

int Breeder::countBarnWealth() {
	vector<BarnItem *> items;
	this->barn.getAllItem(items);

	int wealth = 0;
	for (const auto &itemPtr : items)
		wealth += itemPtr->getPrice();
	return wealth;
}

const int BreederUntaxed = 11;
int Breeder::calculateTax() {
	int wealth = this->money + this->countInventoryWealth() + this->countBarnWealth();
	int taxed = wealth - BreederUntaxed;
	int bracket = getTaxBracket(taxed);
	return max((int)round((taxed * bracket) / 100.0), 0);
}
