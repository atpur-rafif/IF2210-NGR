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
	int barnCount;
	inputStream >> barnCount;
	while (barnCount--) {
		int animalWeight;
		string location, name;
		inputStream >> location >> name >> animalWeight;
		string code = ctx.itemFactory.getCodeByName(name);
		BarnItem item;
		ctx.itemFactory.createItem(code, item);
		item.setWeight(animalWeight);
		this->barn.setItem(location, item);
	}
}

void Breeder::writeSpecializedConfig(ostream &outputStream) {
	auto barnItems = this->barn.getAllItemWithCoordinate();
	outputStream << barnItems.size() << endl;
	for (auto it : barnItems) {
		auto item = it.second;
		outputStream << it.first << ' ' << item->getName() << ' ' << item->getWeight() << endl;
	}
};
