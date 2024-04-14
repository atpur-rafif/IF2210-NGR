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

/**
 * ISSUE:
 * Muncul animal di coordinate lain padahal aslinya gada, tapi pas diharvest bisa, item yang lain bisa ikut ilang
 */
void Breeder::harvestAnimal(string &coordinate) {
	pair<string, string> special = {"DCK", "CHK"};
	bool isSpecial = false;
	optional<BarnItem> harvestedAnimal = this->barn.getItem(coordinate);
	string code;
	string code2;
	if (harvestedAnimal.has_value()) {
		if (harvestedAnimal.value().getWeight() < harvestedAnimal.value().getWeightToHarvest()) {
			throw InvalidHarvestException();
		}

		code = this->getContext().getItemFactory().getProductResult(harvestedAnimal.value().getName(), "");
		if (code.empty()) {
			throw InvalidBarnProductNotFoundException();
		}
		if (harvestedAnimal.value().getCode() == special.first || harvestedAnimal.value().getCode() == special.second) {
			isSpecial = true;
			code2 = this->getContext().getItemFactory().getProductResult(harvestedAnimal.value().getName(), code);
			if (code2.empty()) {
				throw InvalidBarnProductNotFoundException();
			}
		}
	} else {
		throw InvalidFieldEmptyException();
	}
	ProductItem animal_product;
	this->getContext().getItemFactory().createItem(code, animal_product);
	shared_ptr<Item> newItem = make_shared<ProductItem>(animal_product);
	this->inventory.addItem(newItem);
	this->barn.clearItem(coordinate);
	if (isSpecial) {
		ProductItem animal_product2;
		this->getContext().getItemFactory().createItem(code2, animal_product2);
		shared_ptr<Item> newItem2 = make_shared<ProductItem>(animal_product2);
		this->inventory.addItem(newItem2);
		this->barn.clearItem(coordinate);
	}
}
