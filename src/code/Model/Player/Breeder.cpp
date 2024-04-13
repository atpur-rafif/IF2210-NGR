#include "Model/Player/Breeder.hpp"
#include "Controller/GameContext.hpp"
#include <cmath>

Breeder::Breeder() { this->type = BreederType; }
Breeder::~Breeder() {}
Breeder *Breeder::clone() { return new Breeder(*this); }

int Breeder::countBarnWealth() {
	int wealth = 0;
	for (auto &itemPtr : this->barn.getAllItem())
		wealth += itemPtr->getPrice();
	return wealth;
}

const int BreederUntaxed = 11;
int Breeder::calculateTax() {
	int wealth = this->money + this->countInventoryWealth() + this->countBarnWealth();
	int taxed = wealth - BreederUntaxed;
	int bracket = getTaxBracket(taxed);
	int tax = max((int)round((taxed * bracket) / 100.0), 0);
	if (this->money < tax) tax = this->money;
	return tax;
}

void Breeder::readSpecializedConfig(istream &inputStream) {
	auto ctx = this->getContext();
	auto barnSize = ctx.miscConfig.getBarnSize();
	this->barn = Storage<BarnItem>(barnSize.first, barnSize.second);
	int farmCount;
	inputStream >> farmCount;
	while (farmCount--) {
		int age;
		string location, name;
		inputStream >> location >> name >> age;
		string code = ctx.itemFactory.getCodeByName(name);
		BarnItem item;
		ctx.itemFactory.createItem(code, item);
		this->barn.setItem(location, item);
	}
}
