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


void Breeder::placeAnimal(){
	//CETAK_INVENTORY
	cout << "Pilih hewan dari inventory"; 
	//item dari inventory;	
	string slot; 
	cout << "Slot: "; 
	cin >> slot; 

	//animal untuk di place petak tanah
	cout << "Pilih petak tanah: "; 
	string slotPlace; 
	cin >> slotPlace;
	this->barn.setItem(slotPlace, this->inventory.getItem(slot));
}

void Breeder::giveFood(string& coorBarnItem, string& coorFoodItem){
	optional<BarnItem> tempBarn = this->barn.getItem(coorBarnItem);
	optional<Heapify<Item>> tempFood = this->inventory.getItem(coorFoodItem); 
	bool finish = false;
	BarnItem* currAnimal; 
	if(tempBarn.has_value()){
		currAnimal = &tempBarn.value();	
	}
	else{
		throw "Fieldsnya kosong euy";
	}

	Item* food; 
	if(tempFood.has_value()){
		food = tempFood->getRaw(); 
		if(food->getType() != Barn || food->getType() != Farm){
			throw "Bukan sebuah pangan hewan";
		}
	}

	if(currAnimal->getBarnItemType() == Herbivore){
		if(food->getType() == Farm){
			this->inventory.clearItem(coorFoodItem);
			finish = true;
		}
		else{
			throw "Salah woey dia herbivora";
		}
	}
	if(currAnimal->getBarnItemType() == Carnivore){
		if(food->getType() == Barn){
			this->inventory.clearItem(coorFoodItem);
			finish = true;
		}
		else{
			throw "Salah woey dia karnivora";
		}
	}
	if(currAnimal->getBarnItemType() == Omnivore){
		if(food->getType() == Barn || food->getType() == Farm){
			this->inventory.clearItem(coorFoodItem);
			finish = true;
		}
		else{
			throw "Salah makanan dia omnivora";
		}
	}

	if(finish){
		currAnimal->setWeight(currAnimal->getWeight() + 10);
	}
	else{
		throw "Gagal memberi makananan"; 
	}
}

void Breeder::harvestAnimal(string& coordinate){
	optional<BarnItem> tempAnimal = this->barn.getItem(coordinate);

	BarnItem* currAnimal; 
	bool isFinished = false;
	if(tempAnimal.has_value()){
		currAnimal = &tempAnimal.value(); 
	}
	else{
		throw "ini field kosong bjir";
	}

	if(currAnimal->getWeight() != currAnimal->getWeightToHarvest()){
		throw "Belum waktunya panen bosque"; 
	}


	if(currAnimal->getCode() == "COW"){ //COW 

	}
	else if(currAnimal->getCode() == "SHP"){ //SHEEP

	}
	else if (currAnimal->getCode() == "HRS"){ //HORSE

	}
	else if(currAnimal->getCode() == "RBT"){ //RABBIT

	}
	else if(currAnimal->getCode() == "SNK"){ //SNAKE

	}
	else if(currAnimal->getCode() == "CHK"){ //CHICKEN

	}
	else if(currAnimal->getCode() == "DCK"){ //DUCK

	}
	else{
		throw "Kode salah";
	}
	
	
}