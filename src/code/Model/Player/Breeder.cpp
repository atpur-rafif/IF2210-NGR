#include "Model/Player/Breeder.hpp"
#include "Controller/GameContext.hpp"
#include "Exception/ItemFactoryException.hpp"
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
		string code = ctx.getItemFactory().getCodeByName(name);
		BarnItem item;
		ctx.getItemFactory().createItem(code, item);
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
	auto itemOptional = this->inventory.getItem(locInventory);
	if (!itemOptional.has_value()) {
		throw InvalidItemNotFoundException();
	}
	shared_ptr<Item> item = itemOptional.value();
	if (item->getType() != Barn) {
		throw InvalidTypeValueException();
	}
	BarnItem *newAnimal = dynamic_cast<BarnItem *>(item.get());
	if (newAnimal == NULL) {
		throw InvalidDowncastException();
	}
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
	BarnItem *animal = nullptr;
	auto &tempBarn = this->barn.getItem(animalLocation);

	if (!tempBarn.has_value()) {
		throw InvalidFieldEmptyException();
	}

	animal = &tempBarn.value();
	auto optionalItem = this->inventory.getItem(foodLocation);
	if (!optionalItem.has_value()) {
		throw InvalidItemNotFoundException();
	}
	shared_ptr<Item> itemFoodTemp = optionalItem.value();
	ProductItem *itemFood = dynamic_cast<ProductItem *>(itemFoodTemp.get());

	if (!itemFood) {
		throw InvalidNotFoodException();
	}

	if (itemFood->getProductItemType() == MaterialProduct) {
		throw InvalidNotFoodException();
	}

	if (animal->getBarnItemType() == Herbivore) {
		if (itemFood->getProductItemType() != FruitProduct) {
			throw InvalidFoodHerbivores();
		}
	} else if (animal->getBarnItemType() == Carnivore) {
		if (itemFood->getProductItemType() != AnimalProduct) {
			throw InvalidFoodCarnivores();
		}
	}
	this->inventory.clearItem(foodLocation);
	animal->setWeight(animal->getWeight() + itemFood->getAddedWeight());
}

void Breeder::harvestAnimal(string &coordinate) {
	auto &ctx = this->getContext();
	auto &itemFactory = ctx.getItemFactory();

	optional<BarnItem> harvestedAnimal = this->barn.getItem(coordinate);
	if (!harvestedAnimal.has_value())
		throw InvalidFieldEmptyException();

	BarnItem &item = harvestedAnimal.value();
	vector<string> results = itemFactory.getProductResults(item.getCode());

	this->barn.clearItem(coordinate);
	for (auto code : results) {
		shared_ptr<Item> item = itemFactory.createBaseItem(code);
		this->inventory.addItem(item);
	}
}
