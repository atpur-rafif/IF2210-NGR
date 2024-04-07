#include "Model/Item.hpp"

int Item::getPrice() { return this->price; }
int Item::getId() { return this->id; }
string Item::getCode() { return this->code; }
string Item::getName() { return this->name; }
ItemType Item::getType() { return this->type; }

Item::Item() {}
Item::~Item(){};

istream &operator>>(istream &inputStream, Item &item) {
	inputStream >> item.id;
	inputStream >> item.code;
	inputStream >> item.name;
	item.readAttributeFromStream(inputStream);
	inputStream >> item.price;
	return inputStream;
}