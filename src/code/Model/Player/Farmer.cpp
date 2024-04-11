#include "Model/Player/Farmer.hpp"
#include "../header/Model/Item/ProductItem.hpp"
#include <algorithm>
#include <cmath>
#include <optional>
using namespace std;

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

void Farmer::plant(string &invLocation, string &fieldLocation) {
	auto inv_item = this->inventory.getItem(invLocation);
	Item *item = inv_item.value().getRaw();
	FarmItem *selected_plant = dynamic_cast<FarmItem* >(item);
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
	optional<FarmItem> harvested_item = this->farm.getItem(coordinate);
	auto *itemFactory = &this->getContext().itemFactory; 
	string code = itemFactory->getProductResult(harvested_item);
	ProductItem *harvest_product;
	Heapify<Item> base_product = itemFactory->createBaseItem(code);
	itemFactory->createItem(code, harvest_product);
	this->inventory.addItem(base_product);
	this->farm.clearItem(coordinate);
}




