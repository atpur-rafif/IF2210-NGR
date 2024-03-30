#include "Item.hpp"
#include <sstream>
#include <string>

int Item::getPrice() { return this->price; }
int Item::getId() { return this->id; }
string Item::getCode() { return this->code; }
string Item::getName() { return this->name; }
ItemType Item::getType() { return this->type; }

Item::Item() : id(-1), code("   ") {}
ProductItem::ProductItem() { this->type = Product; }
FarmItem::FarmItem() { this->type = Farm; }
BarnItem::BarnItem() { this->type = Barn; }
BuildingItem::BuildingItem() { this->type = Building; }

Item::~Item(){};
ProductItem::~ProductItem() {}
FarmItem::~FarmItem() {}
BarnItem::~BarnItem() {}
BuildingItem::~BuildingItem() {}

ProductItem *ProductItem::clone() const { return new ProductItem(*this); }
FarmItem *FarmItem::clone() const { return new FarmItem(*this); }
BarnItem *BarnItem::clone() const { return new BarnItem(*this); }
BuildingItem *BuildingItem::clone() const { return new BuildingItem(*this); }

ProductItemType ProductItem::getProductItemType() { return this->productItemType; }
FarmItemType FarmItem::getFarmItemType() { return this->farmItemType; }
BarnItemType BarnItem::getBarnItemType() { return this->barnItemType; }

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
istream &operator>>(istream &inputStream, BuildingItem &item) {
	inputStream >> item.id;
	inputStream >> item.code;
	inputStream >> item.name;
	inputStream >> item.price;
	item.readAttributeFromStream(inputStream);
	return inputStream;
}

void ProductItem::readAttributeFromStream(istream &inputStream) {
	string type;
	inputStream >> type;
	if (type == "PRODUCT_MATERIAL_PLANT") this->productItemType = MaterialPlant;
	else if (type == "PRODUCT_FRUIT_PLANT") this->productItemType = MaterialPlant;
	else if (type == "PRODUCT_ANIMAL") this->productItemType = Animal;

	inputStream >> this->origin;
	inputStream >> this->addedWeight;
}

void FarmItem::readAttributeFromStream(istream &inputStream) {
	string type;
	inputStream >> type;
	if (type == "MATERIAL_PLANT") this->farmItemType = Material;
	else if (type == "FRUIT_PLANT") this->farmItemType = Fruit;
	inputStream >> this->durationToHarvest;
}

void BarnItem::readAttributeFromStream(istream &inputStream) {
	string type;
	inputStream >> type;
	if (type == "HERBIVORE") this->barnItemType = Herbivore;
	else if (type == "CARNIVORE") this->barnItemType = Carnivore;
	else if (type == "OMNIVORE") this->barnItemType = Omnivore;

	inputStream >> this->weightToHarvest;
}

map<string, int> *BuildingItem::getIngredients() {
	return &this->building;
};

void BuildingItem::readAttributeFromStream(istream &inputStream) {
	string line;
	getline(inputStream, line);
	istringstream lineStream(line);

	while (lineStream.peek() != EOF) {
		string material;
		int count;
		lineStream >> material >> count >> ws;
		this->building[material] = count;
	}
}
