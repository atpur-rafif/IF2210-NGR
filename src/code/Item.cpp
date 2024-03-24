#include "Item.hpp"
#include <sstream>
#include <string>

int Item::getPrice() { return this->price; }
int Item::getId() { return this->id; }
string Item::getCode() { return this->code; }
string Item::getName() { return this->name; }

InventoryItem::InventoryItem() {}
FarmItem::FarmItem() {}
BarnItem::BarnItem() {}
RecipeItem::RecipeItem() {}

Item::~Item(){};
InventoryItem::~InventoryItem() {}
FarmItem::~FarmItem() {}
BarnItem::~BarnItem() {}
RecipeItem::~RecipeItem() {}

InventoryItemType InventoryItem::getType() { return this->type; }
FarmItemType FarmItem::getType() { return this->type; }
BarnItemType BarnItem::getType() { return this->type; }

int FarmItem::getAge() { return this->currentAge; }
void FarmItem::setAge(int age) { this->currentAge = age; }
int BarnItem::getWeight() { return this->currentWeight; }
void BarnItem::setWeight(int weight) { this->currentWeight = weight; }

istream &
operator>>(istream &inputStream, Item &item) {
	inputStream >> item.id;
	inputStream >> item.code;
	inputStream >> item.name;
	item.readAttributeFromStream(inputStream);
	inputStream >> item.price;
	return inputStream;
}

// Don't we love exception???
istream &operator>>(istream &inputStream, RecipeItem &item) {
	inputStream >> item.id;
	inputStream >> item.code;
	inputStream >> item.name;
	inputStream >> item.price;
	item.readAttributeFromStream(inputStream);
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

map<string, int> *RecipeItem::getIngredients() {
	return &this->recipe;
};

void RecipeItem::readAttributeFromStream(istream &inputStream) {
	string line;
	getline(inputStream, line);
	istringstream lineStream(line);

	while (lineStream.peek() != EOF) {
		string material;
		int count;
		lineStream >> material >> count >> ws;
		this->recipe[material] = count;
	}
}
