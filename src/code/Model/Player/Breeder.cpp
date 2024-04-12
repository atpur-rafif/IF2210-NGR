#include "Model/Player/Breeder.hpp"
#include <cmath>

Breeder::Breeder() { this->type = BreederType; }
Breeder::~Breeder() {}
Breeder *Breeder::clone() { return new Breeder(*this); }

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
	return max((int)round((taxed * bracket) / 100.0), 0);
}


void Breeder::placeAnimal(string& locInventory, string& locField){
    auto itemOptional = this->inventory.getItem(locInventory);
    if(!itemOptional.has_value()){
        throw InvalidItemNotFoundException();
    }
    shared_ptr<Item> item = itemOptional.value();
    if(item->getType() != Barn){
        throw InvalidTypeValueException(); 
    }
    BarnItem* newAnimal = dynamic_cast<BarnItem*>(item.get());
    if(newAnimal == NULL){
        throw InvalidDowncastException();
    }
    this->barn.setItem(locField, *newAnimal);
    this->inventory.clearItem(locInventory);
}

void Breeder::giveFood(string& locInventory, string& locField) {
    BarnItem* currAnimal = nullptr;
    auto tempBarn = this->barn.getItem(locField);

    if(!tempBarn.has_value()){
        throw InvalidBarnEmpty();
    }
    
    currAnimal = &tempBarn.value();
    auto optionalItem = this->inventory.getItem(locInventory);
    if(!optionalItem.has_value()){
        throw InvalidItemNotFoundException();
    }
    shared_ptr<Item> itemFoodTemp = optionalItem.value();
    ProductItem* itemFood = dynamic_cast<ProductItem*>(itemFoodTemp.get());

    if (!itemFood) {
        throw InvalidTypeException();
    }

    if (itemFood->getProductItemType() == MaterialProduct) {
        throw InvalidNotFoodException();
    }

    if (currAnimal->getBarnItemType() == Herbivore) {
        if (itemFood->getProductItemType() != FruitProduct) {
            throw InvalidFoodHerbivores();
        }
    } else if (currAnimal->getBarnItemType() == Carnivore) {
        if (itemFood->getProductItemType() != AnimalProduct) {
            throw InvalidFoodCarnivores();
        }
    }

    this->inventory.clearItem(locInventory);
    currAnimal->setWeight(currAnimal->getWeight() + 10);
}

void Breeder::harvestAnimal(string& coordinate){
	optional<BarnItem> harvestedAnimal = this->barn.getItem(coordinate);
	string code; 
	if(harvestedAnimal.has_value()){
		code = this->getContext().itemFactory.getProductResult(harvestedAnimal.value().getName()); 
        cout << code << endl;
        if(code.empty()){
            throw InvalidBarnProductNotFoundException();
        }
	}
	else{
		throw InvalidBarnEmpty();
	}
	ProductItem animal_product; 
	this->getContext().itemFactory.createItem(code, animal_product); 
    shared_ptr<Item> newItem = make_shared<ProductItem>(animal_product); 
    this->inventory.addItem(newItem);
	this->barn.clearItem(coordinate);
}