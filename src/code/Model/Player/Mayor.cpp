#include "Model/Player/Mayor.hpp"
#include "Model/Item/BuildingItem.hpp"
#include "Controller/GameContext.hpp"
#include "Exception/PlayerException.hpp"
#include <sstream>

#define MINIMUM_MONEY 50

Mayor::Mayor() { this->type = MayorType; }
Mayor::~Mayor() {}
Mayor *Mayor::clone() { return new Mayor(*this); }

vector<pair<shared_ptr<Player>, int>> Mayor::collectTax() {
	vector<pair<shared_ptr<Player>,int>> result;
	pair<shared_ptr<Player>, int> inserter;
	auto players = this->getContext().players.getPlayers();
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
	sort(result.begin(),result.end(),[this](const pair<shared_ptr<Player>, int>& elOne,const pair<shared_ptr<Player>, int>& elTwo){
		return elTwo.second < elOne.second;
	});
	return result;
}

int Mayor::calculateTax() {
	return 0;
}

void Mayor::getRecipe(map<string,map<string,int>> &recipe){
	for (const auto& pair : this->getContext().itemFactory.getRepository()) {
		if(pair.second.get()->getType()==Building){
			Item* base = pair.second.get();
			BuildingItem* derived = dynamic_cast<BuildingItem*>(base);
			auto ingredients = derived->getIngredients();
			for (auto it = ingredients->begin(); it != ingredients->end(); ++it) {
				recipe[pair.second.get()->getName()][it->first] = it->second;
			}
			recipe[pair.second.get()->getName()]["GULDEN"] = derived->getPrice();
		}
	}
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
		shared_ptr<Item> buildPtr = make_shared<BuildingItem>(build);
		this->inventory.addItem(buildPtr);
		this->money -= build.getPrice();
	}
}


void Mayor::addPlayer(string username,string type){
	transform(next(type.begin()),type.end(),next(type.begin()),::tolower);
	transform(type.begin(),next(type.begin()),type.begin(),::toupper);
	if(type=="Walikota") throw "Invalid player type";
	string weight = "0";
	string money = "50";
	string inventoryCount = "0";
	string specialInventoryCount = "0";
	string inserter = username + " " + type + " " + weight + " " + money + " " + inventoryCount + " " + specialInventoryCount;
	istringstream inputStream(inserter);
	shared_ptr<Player> player = this->getContext().players.readPlayerFromStream(inputStream);
	this->money -= 50;
	this->getContext().players.addPlayer(player);
	if(this->username>username || PlayerController::toLower(this->username)>PlayerController::toLower(username)){
		this->getContext().players.nextPlayer();
	} 
}

void Mayor::isEnoughMoney(){
	if(this->money<MINIMUM_MONEY) throw NotEnoughResourceException();
}
