#include "Model/Item/FarmItem.hpp"

FarmItem::FarmItem() { this->type = Farm; }
FarmItem::~FarmItem() {}
FarmItem *FarmItem::clone() const { return new FarmItem(*this); }

FarmItemType FarmItem::getFarmItemType() { return this->farmItemType; }

int FarmItem::getAge() { return this->currentAge; }
void FarmItem::setAge(int age) { this->currentAge = age; }

bool FarmItem::harvestable() { return this->getAge() >= this->getDurationToHarvest(); }
void FarmItem::readHarvestState(istream &inputStream) { inputStream >> this->currentAge; };
void FarmItem::writeHarvestState(ostream &outputStream) { outputStream << this->currentAge; };

void FarmItem::readAttributeFromStream(istream &inputStream) {
	string type;
	inputStream >> type;
	if (type == "MATERIAL_PLANT") this->farmItemType = Material;
	else if (type == "FRUIT_PLANT") this->farmItemType = Fruit;
	inputStream >> this->durationToHarvest;
}

int FarmItem::getDurationToHarvest() { return this->durationToHarvest; }
