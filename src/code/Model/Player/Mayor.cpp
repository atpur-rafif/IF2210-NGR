#include "Model/Player/Mayor.hpp"
#include "Model/Item/BuildingItem.hpp"
#include "Controller/GameContext.hpp"
#include "Exception/PlayerException.hpp"

Mayor::Mayor() { this->type = MayorType; }
Mayor::~Mayor() {}
Mayor *Mayor::clone() { return new Mayor(*this); }

map<string, int> Mayor::collectTax() {
	map<string, int> result;
	auto &players = *this->getContext().players.getPlayers();
	int size = players.size();
	for (int i = 0; i < size; ++i) {
		auto &income = players[i];
		if (income->type == MayorType) continue;
		int tax = income->calculateTax();
		income->money -= tax;
		this->money += tax;
		result[income->username] = tax;
	}
	return result;
}

int Mayor::calculateTax() {
	return 0;
}

void Mayor::buildBuilding(string recipe){
	map<string, int> inventoryFreq = this->inventory.getItemFreq();
	map<string, int> remainingIngredient;
	bool enoughResource = true;
	BuildingItem build;
	int remainingMoney;
	this->getContext().itemFactory.createItem(recipe,build);
	remainingMoney  = build.getPrice()-this->money;
	for(auto it=build.getIngredients()->cbegin();it!=build.getIngredients()->cend(); ++it){
		if(it->second - inventoryFreq[it->first]>0){
		remainingIngredient[it->first] = it->second - inventoryFreq[it->first];
		if(remainingIngredient[it->first]>0) enoughResource = false;
		}
	}
	if(!enoughResource || remainingMoney>0){
		throw NotEnoughResourceException(remainingIngredient,remainingMoney);
	}
	else{
		for(auto it=build.getIngredients()->cbegin();it!=build.getIngredients()->cend(); ++it){
			for(int i=0;i<it->second;i++){
				this->inventory.removeItem(it->first);
			}
		}
		this->inventory.addItem(&build);
		this->money -= build.getPrice();
	}
}


void Mayor::addPlayer(){

}
