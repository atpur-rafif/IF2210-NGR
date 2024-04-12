#include "Model/Player/Farmer.hpp"
#include <algorithm>
#include <cmath>
#include <optional>

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
	return max((int)round((taxed * bracket) / 100.0), 0);
}

void Farmer::plant(string &invLocation, string &fieldLocation) {
	auto inv_item = this->inventory.getItem(invLocation);
	if (!inv_item.has_value())
	{
		throw;
	}
	shared_ptr<Item> item = inv_item.value();
	if (item->getType() != Farm)
	{
		throw;
	}
	FarmItem *selected_plant = dynamic_cast<FarmItem* >(item.get());
	if (selected_plant == NULL)
	{
		throw;
	}
	else 
	{
		this->farm.setItem(fieldLocation, *selected_plant);
		this->inventory.clearItem(invLocation);
	}
}

void Farmer::harvestPlant(string& coordinate) {
	cout << coordinate << endl;
	optional<FarmItem> harvested_item = this->farm.getItem(coordinate);
	string code;
	if (harvested_item.has_value())
	{
		code = this->getContext().itemFactory.getProductResult(harvested_item);
	}
	if (code.empty())
	{
		throw;
	}
	shared_ptr<FarmItem> harvest_product;
	this->getContext().itemFactory.createItem(code, harvest_product);
	this->inventory.addItem(harvest_product);
	this->farm.clearItem(coordinate);
}