#include "Model/Player/Farmer.hpp"
#include "Controller/GameContext.hpp"
#include <algorithm>
#include <cmath>

Farmer::Farmer() { this->type = FarmerType; }
Farmer::~Farmer() {}
Farmer *Farmer::clone() { return new Farmer(*this); }

void Farmer::readSpecializedConfig(istream &inputStream) { this->readFieldFromStream(inputStream); }
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

void Farmer::plant(string &inventoryLocation, string &fieldLocation) {
	auto opt = this->inventory.getItem(inventoryLocation);
	if (!opt.has_value())
		throw GameException("Empty inventory slot when planting");

	shared_ptr<Item> item = opt.value();
	FarmItem *newPlant = dynamic_cast<FarmItem *>(item.get());
	if (newPlant == nullptr)
		throw GameException("Can't plant non farm item");

	this->field.setItem(fieldLocation, *newPlant);
	this->inventory.clearItem(inventoryLocation);
}

void Farmer::harvestPlant(string &coordinate) {
	auto &itemFactory = this->getContext().getItemFactory();
	optional<FarmItem> &opt = this->field.getItem(coordinate);
	if (!opt.has_value())
		throw GameException("Empty farm slot given when harvesting");

	auto &item = opt.value();

	vector<string> results = itemFactory.getProductResults(item.getName());
	if (results.size() == 0)
		throw GameException("Plant doesn't have any product result");

	for (auto &name : results) {
		shared_ptr<Item> item = itemFactory.createBaseItemByName(name);
		this->inventory.addItem(item);
	}
	this->field.clearItem(coordinate);
}

void Farmer::plantsGrow() {
	for (FarmItem *plant : this->field.getAllItem()) {
		plant->setAge(plant->getAge() + 1);
	}
}
