#include "Model/Player/Breeder.hpp"
#include "Controller/GameContext.hpp"
#include <cmath>

Breeder::Breeder() { this->type = BreederType; }
Breeder::~Breeder() {}
Breeder *Breeder::clone() { return new Breeder(*this); }

Storage<BarnItem> &Breeder::getBarn() { return this->barn; };

int Breeder::countBarnWealth() {
	int wealth = 0;
	for (auto &itemPtr : this->barn.getAllItem())
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

void Breeder::readSpecializedConfig(istream &inputStream) {
	auto &ctx = this->getContext();
	auto &misc = ctx.getMiscConfig();
	this->barn = Storage<BarnItem>(misc.getBarnWidth(), misc.getFarmHeight());
	int barnCount;
	inputStream >> barnCount;
	while (barnCount--) {
		int animalWeight;
		string location, name;
		inputStream >> location >> name >> animalWeight;
		BarnItem item;
		ctx.getItemFactory().createItemByName(name, item);
		item.setWeight(animalWeight);
		this->barn.setItem(location, item);
	}
}

void Breeder::writeSpecializedConfig(ostream &outputStream) {
	auto barnItems = this->barn.getAllItemWithCoordinate();
	outputStream << barnItems.size() << endl;
	for (auto it : barnItems) {
		auto item = it.second;
		outputStream << it.first << ' ' << item->getName() << ' ' << item->getWeight() << endl;
	}
};

void Breeder::placeAnimal(string &locInventory, string &locField) {
	auto opt = this->inventory.getItem(locInventory);
	if (!opt.has_value())
		throw GameException("Empty inventory slot when breeding");

	shared_ptr<Item> item = opt.value();
	BarnItem *newAnimal = dynamic_cast<BarnItem *>(item.get());
	if (newAnimal == nullptr)
		throw GameException("Can't put non barn item to barn");

	this->barn.setItem(locField, *newAnimal);
	this->inventory.clearItem(locInventory);
}

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
	auto &tempBarn = this->barn.getItem(animalLocation);

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

void Breeder::harvestAnimal(string &coordinate) {
	auto &ctx = this->getContext();
	auto &itemFactory = ctx.getItemFactory();

	optional<BarnItem> harvestedAnimal = this->barn.getItem(coordinate);
	if (!harvestedAnimal.has_value())
		throw GameException("Empty animal slot when harvesting");

	BarnItem &item = harvestedAnimal.value();
	vector<string> results = itemFactory.getProductResults(item.getName());

	this->barn.clearItem(coordinate);
	for (auto name : results) {
		shared_ptr<Item> item = itemFactory.createBaseItemByName(name);
		this->inventory.addItem(item);
	}
}
