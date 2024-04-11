#include "Model/Player/Mayor.hpp"
#include "Model/Item/BuildingItem.hpp"
#include "Controller/GameContext.hpp"
#include "Exception/PlayerException.hpp"

Mayor::Mayor() { this->type = MayorType; }
Mayor::~Mayor() {}
Mayor *Mayor::clone() { return new Mayor(*this); }

vector<pair<Player*, int>> Mayor::collectTax() {
	vector<pair<Player*,int>> result;
	pair<Player*, int> inserter;
	auto &players = *this->getContext().players.getPlayers();
	int size = players.size();
	for (int i = 0; i < size; ++i) {
		auto &income = players[i];
		if (income->type == MayorType) continue;
		int tax = income->calculateTax();
		income->money -= tax;
		this->money += tax;
		inserter.first = income;
		inserter.second = tax;
		result.push_back(inserter);
	}
	sort(result.begin(),result.end(),[this](const pair<Player*, int>& elOne,const pair<Player*, int>& elTwo){
		return elTwo.second < elOne.second;
	});
	return result;
}

int Mayor::calculateTax() {
	return 0;
}
map<string,map<string,int>> Mayor::getRecipe(){
	map<string,map<string,int>> recipe;
	for (const auto& pair : this->getContext().itemFactory.getRepository()) {
		if(pair.second.get().getType()==3){
			Item* base = &pair.second.get();
			BuildingItem* derived = dynamic_cast<BuildingItem*>(base);
			auto ingredients = derived->getIngredients();
			for (auto it = ingredients->begin(); it != ingredients->end(); ++it) {
				recipe[pair.second.get().getName()][it->first] = it->second;
			}
			recipe[pair.second.get().getName()]["GULDEN"] = derived->getPrice();
		}
	}
	return recipe;
} 

void Mayor::buildBuilding(string recipe){
	map<string, int> inventoryFreq = this->inventory.getItemFreq();
	map<string, int> remainingIngredient;
	string code = this->getContext().itemFactory.getCodeByName(recipe);
	bool enoughResource = true;
	BuildingItem build;
	int remainingMoney;
	this->getContext().itemFactory.createItem(code,build);
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


void Mayor::addPlayer(string username,string type){
	transform(type.begin(),type.end(),type.begin(),::tolower);
	int weight = 0;
	int money = 50;
	Heapify<Player> player = this->getContext().players.createPlayerFromParam(weight,money,username,type);
	this->money -= 50;
	this->getContext().players.addPlayer(player);
}

void Mayor::isEnoughMoney(int money){
	if(this->money<money) throw NotEnoughResourceException();
}
