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
	int tax = max((int)round((taxed * bracket) / 100.0), 0);
	if(this->money<tax) tax = this->money;
	return tax;
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

void Breeder::giveFoodChecker(string& locField){
   BarnItem* currAnimal = nullptr;
    auto tempBarn = this->barn.getItem(locField);

    if(!tempBarn.has_value()){
        throw InvalidFieldEmptyException();
    }
    
    currAnimal = &tempBarn.value();
    vector<ProductItem*> foodchecker; 
    vector<shared_ptr<Item>* > repo = this->inventory.getAllItem();
    for(auto& itemPtr: repo){
        shared_ptr<Item> rawPtr = *itemPtr;
        if(auto productItemPtr = dynamic_cast<ProductItem*>(rawPtr.get())){
            foodchecker.push_back(productItemPtr);
        }
    }

    bool isFound = false; 
    if(currAnimal->getBarnItemType() == Carnivore){
        for(const auto& item : foodchecker){
            if(item->getProductItemType() == AnimalProduct){
                isFound = true;
            }
        }
    }
    else if(currAnimal->getBarnItemType() == Herbivore){
        for(const auto& item : foodchecker){
            if(item->getProductItemType() == FruitProduct){
                isFound = true;
            }
        }
        
    }
    else if(currAnimal->getBarnItemType() == Omnivore){
        for(const auto& item : foodchecker){
            if(item->getProductItemType() == AnimalProduct || item->getProductItemType() == FruitProduct){
                isFound = true;
            }
        }
    } 
    if(!isFound){
        throw InvalidFoodNotFoundException();
    }
}

void Breeder::giveFood(string& locInventory, string& locField) {
    BarnItem* currAnimal = nullptr;
    auto tempBarn = this->barn.getItem(locField);

    if(!tempBarn.has_value()){
        throw InvalidFieldEmptyException();
    }
    
    currAnimal = &tempBarn.value();

    auto optionalItem = this->inventory.getItem(locInventory);
    if(!optionalItem.has_value()){
        throw InvalidItemNotFoundException();
    }
    shared_ptr<Item> itemFoodTemp = optionalItem.value();
    ProductItem* itemFood = dynamic_cast<ProductItem*>(itemFoodTemp.get());

    if (!itemFood) {
        throw InvalidNotFoodException();
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
    currAnimal->setWeight(currAnimal->getWeight() + itemFood->getAddedWeight());
}

/**
 * ISSUE: 
 * Muncul animal di coordinate lain padahal aslinya gada, tapi pas diharvest bisa, item yang lain bisa ikut ilang 
*/
void Breeder::harvestAnimal(string& coordinate){
    pair<string, string> special = {"DCK", "CHK"};
    bool isSpecial = false;
	optional<BarnItem> harvestedAnimal = this->barn.getItem(coordinate);
	string code; 
    string code2;
	if(harvestedAnimal.has_value()){
        if(harvestedAnimal.value().getWeight() < harvestedAnimal.value().getWeightToHarvest()){
            throw InvalidHarvestException();
        }

		code = this->getContext().itemFactory.getProductResult(harvestedAnimal.value().getName(), ""); 
        if(code.empty()){
            throw InvalidBarnProductNotFoundException();
        }
        if(harvestedAnimal.value().getCode() == special.first || harvestedAnimal.value().getCode() == special.second){
            isSpecial = true;
            code2 = this->getContext().itemFactory.getProductResult(harvestedAnimal.value().getName(), code); 
            if(code2.empty()){
                throw InvalidBarnProductNotFoundException();
            }
        }
	}
	else{
		throw InvalidFieldEmptyException();
	}
	ProductItem animal_product; 
	this->getContext().itemFactory.createItem(code, animal_product); 
    shared_ptr<Item> newItem = make_shared<ProductItem>(animal_product); 
    this->inventory.addItem(newItem);
	this->barn.clearItem(coordinate);
    if(isSpecial){
        ProductItem animal_product2;
        this->getContext().itemFactory.createItem(code2, animal_product2); 
        shared_ptr<Item> newItem2 = make_shared<ProductItem>(animal_product2); 
        this->inventory.addItem(newItem2);
	    this->barn.clearItem(coordinate);
    }
}