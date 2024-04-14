#include "Model/Item/BarnItem.hpp"

BarnItem::BarnItem() { this->type = Barn; }
BarnItem::~BarnItem() {}
BarnItem *BarnItem::clone() const { return new BarnItem(*this); }

BarnItemType BarnItem::getBarnItemType() { return this->barnItemType; }

int BarnItem::getWeightToHarvest() { return this->weightToHarvest; }
int BarnItem::getWeight() { return this->currentWeight; }
void BarnItem::setWeight(int weight) { this->currentWeight = weight; }

void BarnItem::readAttributeFromStream(istream &inputStream) {
	string type;
	inputStream >> type;
	if (type == "HERBIVORE") this->barnItemType = Herbivore;
	else if (type == "CARNIVORE") this->barnItemType = Carnivore;
	else if (type == "OMNIVORE") this->barnItemType = Omnivore;

	inputStream >> this->weightToHarvest;
}
