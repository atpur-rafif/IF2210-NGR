#include "Model/Player/Farmer.hpp"
#include "Controller/GameContext.hpp"
#include <algorithm>
#include <cmath>

Farmer::Farmer() { this->type = FarmerType; }
Farmer::~Farmer() {}
Farmer *Farmer::clone() { return new Farmer(*this); }

int Farmer::countFarmWealth() {
	int wealth = 0;
	for (auto &itemPtr : this->farm.getAllItem())
		wealth += itemPtr->getPrice();
	return wealth;
}

const int FarmerUntaxed = 13;
int Farmer::calculateTax() {
	int wealth = this->money + this->countInventoryWealth() + this->countFarmWealth();
	int taxed = wealth - FarmerUntaxed;
	int bracket = Player::getTaxBracket(taxed);
	int tax = max((int)round((taxed * bracket) / 100.0), 0);
	if (this->money < tax) tax = this->money;
	return tax;
}

void Farmer::readSpecializedConfig(istream &inputStream) {
	auto ctx = this->getContext();
	auto farmSize = ctx.miscConfig.getFarmSize();
	this->farm = Storage<FarmItem>(farmSize.first, farmSize.second);
	int farmCount;
	inputStream >> farmCount;
	while (farmCount--) {
		int age;
		string location, name;
		inputStream >> location >> name >> age;
		string code = ctx.itemFactory.getCodeByName(name);
		FarmItem item;
		ctx.itemFactory.createItem(code, item);
		this->farm.setItem(location, item);
	}
};
