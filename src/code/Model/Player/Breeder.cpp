#include "Model/Player/Breeder.hpp"
#include <cmath>

Breeder::Breeder() { this->type = BreederType; }
Breeder::~Breeder() {}
Breeder *Breeder::clone() { return new Breeder(*this); }

int Breeder::countBarnWealth(){
	vector<BarnItem *> barnItems;
	this->barn.getAllItem(barnItems);

	int barnWealth = 0;
	for (const auto &itemPtr : barnItems){
		barnWealth += itemPtr->getPrice();
	}
	return barnWealth;
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
	if(itemOptional.has_value()){
		Item* item = (itemOptional.value().getRaw());
		if(item->getType() != Barn){
			throw InvalidTypeValueException(); 
		}
		BarnItem* newAnimal = dynamic_cast<BarnItem* >(item);
        if(newAnimal == NULL){
            throw InvalidDowncastException();
        }
		this->barn.setItem(locField, *newAnimal);
	}
}

void Breeder::giveFood(string& locInventory, string& locField) {
    try {
        BarnItem* currAnimal = nullptr;
        optional<BarnItem>& tempBarn = this->barn.getItem(locField);

        if (!tempBarn.has_value()){
            throw InvalidBarnEmpty();
        }
		
        currAnimal = &tempBarn.value();

        auto tempFood = this->inventory.getItem(locInventory);
        ProductItem* itemFood = dynamic_cast<ProductItem*>(tempFood->getRaw());

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

    } catch (const exception& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void Breeder::harvestAnimal(string& coordinate){
	optional<BarnItem> harvestedAnimal = this->barn.getItem(coordinate);
	string code; 
	if(harvestedAnimal.has_value()){
		code = this->getContext().itemFactory.getProductResult(harvestedAnimal.value().getName()); 
        if(code.empty()){
            throw InvalidBarnProductNotFoundException();
        }
	}
	else{
		throw InvalidBarnEmpty();
	}
	ProductItem animal_product; 
	this->getContext().itemFactory.createItem(code, animal_product); 
	this->barn.clearItem(coordinate);
}