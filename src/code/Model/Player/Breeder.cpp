#include "Model/Player/Breeder.hpp"
#include "Controller/GameContext.hpp"
#include <cmath>

Breeder::Breeder() { this->type = BreederType; }
Breeder::~Breeder() {}
Breeder *Breeder::clone() { return new Breeder(*this); }

void Breeder::readSpecializedConfig(istream &inputStream) { this->readFieldFromStream(inputStream); }
void Breeder::writeSpecializedConfig(ostream &outputStream) { this->writeFieldToStream(outputStream); };

int Breeder::countBarnWealth() {
	int wealth = 0;
	for (auto &itemPtr : this->field.getAllItem())
		wealth += itemPtr->getPrice();
	return wealth;
}

const int BreederUntaxed = 11;
int Breeder::calculateTax() {
	int wealth = this->money + this->countInventoryWealth() + this->countBarnWealth();
	int taxed = wealth - BreederUntaxed;
	int bracket = getTaxBracket(taxed);
	int tax = max((int)round((taxed * bracket) / 100.0), 0);
	if (this->money < tax) tax = this->money;
	return tax;
}

void Breeder::placeAnimal(string &locInventory, string &locField) { this->place(locInventory, locField); }
void Breeder::harvestAnimal(string &coordinate) { this->harvest(coordinate); }

bool Breeder::ableToFeed(BarnItemType animal, ProductItemType product) {
	if (animal == Omnivore && (product == AnimalProduct || product == FruitProduct)) return true;
	else if (animal == Herbivore && product == FruitProduct) return true;
	else if (animal == Carnivore && product == AnimalProduct) return true;
	else return false;
};

bool Breeder::hasProductToFeed(BarnItemType type) {
	auto items = this->inventory.getAllItem();
	for (auto item : items) {
		if ((*item)->getType() != Product) continue;
		auto productType = dynamic_pointer_cast<ProductItem>(*item)->getProductItemType();

		if (Breeder::ableToFeed(type, productType))
			return true;
	}
	return false;
}

void Breeder::giveFood(string &foodLocation, string &animalLocation) {
	auto &tempBarn = this->field.getItem(animalLocation);

	if (!tempBarn.has_value())
		throw GameException("Empty animal slot when giving food");

	auto opt = this->inventory.getItem(foodLocation);
	if (!opt.has_value())
		throw GameException("Empty inventory slot when giving food");

	shared_ptr<Item> food = opt.value();
	ProductItem *product = dynamic_cast<ProductItem *>(food.get());
	BarnItem *animal = &tempBarn.value();

	if (product == nullptr)
		throw GameException("Invalid item type when giving food");

	if (product->getProductItemType() == MaterialProduct)
		throw GameException("Animal can't eat material product");

	auto animalType = animal->getBarnItemType();
	auto productType = product->getProductItemType();
	if (animalType == Herbivore && productType != FruitProduct)
		throw GameException("Herbivore can't eat non fruit product");
	if (animalType == Carnivore && productType != AnimalProduct)
		throw GameException("Carnivore can't eat non animal product");

	this->inventory.clearItem(foodLocation);
	animal->setWeight(animal->getWeight() + product->getAddedWeight());
}
