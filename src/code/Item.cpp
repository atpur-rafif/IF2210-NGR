#include "Item.hpp"

int Item::getPrice() { return this->price; }
int Item::getId() { return this->id; }
string Item::getCode() { return this->code; }
string Item::getName() { return this->name; }

InventoryItem::InventoryItem() {}
FarmItem::FarmItem() {}
BarnItem::BarnItem() {}

InventoryItemType InventoryItem::getType() { return this->type; }
FarmItemType FarmItem::getType() { return this->type; }
BarnItemType BarnItem::getType() { return this->type; }

istream &operator>>(istream &inputStream, Item &item) {
	inputStream >> item.id;
	inputStream >> item.code;
	inputStream >> item.name;
	item.readAttributeFromStream(inputStream);
	inputStream >> item.price;
	return inputStream;
}

void InventoryItem::readAttributeFromStream(istream &inputStream) {
	string type;
	inputStream >> type;
	if (type == "PRODUCT_MATERIAL_PLANT") this->type = MaterialPlant;
	else if (type == "PRODUCT_FRUIT_PLANT") this->type = MaterialPlant;
	else if (type == "PRODUCT_ANIMAL") this->type = Animal;

	inputStream >> this->origin;
	inputStream >> this->addedWeight;
}

void FarmItem::readAttributeFromStream(istream &inputStream) {
	string type;
	inputStream >> type;
	if (type == "MATERIAL_PLANT") this->type = Material;
	else if (type == "FRUIT_PLANT") this->type = Fruit;
	inputStream >> this->durationToHarvest;
}

void BarnItem::readAttributeFromStream(istream &inputStream) {
	string type;
	inputStream >> type;
	if (type == "HERBIVORE") this->type = Herbivore;
	else if (type == "CARNIVORE") this->type = Carnivore;
	else if (type == "OMNIVORE") this->type = Omnivore;

	inputStream >> this->weightToHarvest;
}
