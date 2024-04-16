#include "Model/Player/Farmer.hpp"
#include "Controller/GameContext.hpp"
#include <algorithm>
#include <cmath>

Farmer::Farmer() { this->type = FarmerType; }
Farmer::~Farmer() {}
Farmer *Farmer::clone() { return new Farmer(*this); }

void Farmer::readSpecializedConfig(istream &inputStream) {
	auto &misc = this->getContext().getMiscConfig();
	this->field = Storage<FarmItem>(misc.getFarmWidth(), misc.getFarmHeight());
	this->readFieldFromStream(inputStream);
}
void Farmer::writeSpecializedConfig(ostream &outputStream) { this->writeFieldToStream(outputStream); };

int Farmer::countFarmWealth() {
	int wealth = 0;
	for (auto &itemPtr : this->field.getAllItem())
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

void Farmer::plant(string &inventoryLocation, string &fieldLocation) { this->place(inventoryLocation, fieldLocation); }
void Farmer::harvestPlant(string &coordinate) { this->harvest(coordinate); }

void Farmer::plantsGrow() {
	for (FarmItem *plant : this->field.getAllItem()) {
		plant->setAge(plant->getAge() + 1);
	}
}
