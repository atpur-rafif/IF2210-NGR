#include "Model/Player/Farmer.hpp"
#include "Controller/GameContext.hpp"
#include <algorithm>
#include <cmath>

Farmer::Farmer() { this->type = FarmerType; }
Farmer::~Farmer() {}
Farmer *Farmer::clone() { return new Farmer(*this); }

Storage<FarmItem> &Farmer::getFarm() { return this->farm; };

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
	auto &ctx = this->getContext();
	auto &misc = ctx.getMiscConfig();
	this->farm = Storage<FarmItem>(misc.getFarmWidth(), misc.getFarmHeight());
	int farmCount;
	inputStream >> farmCount;
	while (farmCount--) {
		int plantAge;
		string location, name;
		inputStream >> location >> name >> plantAge;
		FarmItem item;
		ctx.getItemFactory().createItemByName(name, item);
		item.setAge(plantAge);
		this->farm.setItem(location, item);
	}
};

void Farmer::writeSpecializedConfig(ostream &outputStream) {
	auto farmItems = this->farm.getAllItemWithCoordinate();
	outputStream << farmItems.size() << endl;
	for (auto it : farmItems) {
		auto item = it.second;
		outputStream << it.first << ' ' << item->getName() << ' ' << item->getAge() << endl;
	}
};
void Farmer::plant(string &invLocation, string &fieldLocation) {
	auto inv_item = this->inventory.getItem(invLocation);
	if (!inv_item.has_value()) {
		throw InvalidItemNotFoundException();
	}
	shared_ptr<Item> item = inv_item.value();
	if (item->getType() != Farm) {
		throw InvalidTypeValueException();
	}
	FarmItem *selected_plant = dynamic_cast<FarmItem *>(item.get());
	if (selected_plant == NULL) {
		throw InvalidDowncastException();
	}
	selected_plant->setAge(0);
	this->farm.setItem(fieldLocation, *selected_plant);
	this->inventory.clearItem(invLocation);
}

void Farmer::harvestPlant(string &coordinate) {
	optional<FarmItem> harvested_item = this->farm.getItem(coordinate);
	string code;
	if (harvested_item.has_value()) {
		code = this->getContext().getItemFactory().getProductResult(harvested_item.value().getName(), "");
	}
	if (code.empty()) {
		throw InvalidFarmProductNotFoundException();
	}
	ProductItem harvest_product;
	this->getContext().getItemFactory().createItemByName(code, harvest_product);
	shared_ptr<Item> addedItem = make_shared<ProductItem>(harvest_product);
	this->inventory.addItem(addedItem);
	this->farm.clearItem(coordinate);
}

void Farmer::plantsGrow() {
	for (FarmItem *plant : this->farm.getAllItem()) {
		plant->setAge(plant->getAge() + 1);
	}
}
