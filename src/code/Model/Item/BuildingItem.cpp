#include "Model/Item/BuildingItem.hpp"
#include <sstream>

BuildingItem::BuildingItem() { this->type = Building; }
BuildingItem::~BuildingItem() {}
BuildingItem *BuildingItem::clone() const { return new BuildingItem(*this); }

map<string, int> &BuildingItem::getIngredients() {
	return this->building;
};

// Don't we love exception???
istream &operator>>(istream &inputStream, BuildingItem &item) {
	inputStream >> item.id;
	inputStream >> item.code;
	inputStream >> item.name;
	inputStream >> item.price;
	item.readAttributeFromStream(inputStream);
	return inputStream;
}

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
