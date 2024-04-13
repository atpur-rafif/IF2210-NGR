#include "Controller/PlayerController.hpp"
#include "Controller/GameContext.hpp"
#include "Model/Player/Breeder.hpp"
#include "Model/Player/Farmer.hpp"
#include "Model/Player/Mayor.hpp"
#include "Exception/PlayerControllerException.hpp"
#include <string>
#include <algorithm>

PlayerController::PlayerController() {
	this->currentPlayerIndex = 0;
}

string PlayerController::toLower(string textInput){
	string text = "";
	text += textInput;
	transform(text.begin(),text.end(),text.begin(),::tolower);
	return text; 
}

void PlayerController::nextPlayer() {
	this->currentPlayerIndex = (this->currentPlayerIndex + 1) % this->players.size();
}

shared_ptr<Player> PlayerController::getCurrentPlayer() {
	return this->players.at(this->currentPlayerIndex);
};

void PlayerController::rearrangePosition() {
	auto begin = this->players.begin();
	auto end = begin + this->players.size();
	sort(begin, end, [](shared_ptr<Player> a, shared_ptr<Player> b) {
			return a->username < b->username|| PlayerController::toLower(a->username) < PlayerController::toLower(b->username);
	});
}

void PlayerController::addPlayer(shared_ptr<Player> player) {
	this->players.push_back(player);
	player->setContext(this->getContext());
	this->rearrangePosition();
};

vector<shared_ptr<Player>> PlayerController::getPlayers() {
	return this->players;
}

shared_ptr<Player> PlayerController::readPlayerFromStream(istream &inputStream) {
	int weight, money;
	string username, type;
	inputStream >> username >> type >> weight >> money;
	GameContext &context = this->getContext();

	for(const auto& element : context.players.getPlayers()){
		if(element->username==username) throw UsernameAlreadyExist();
	}

	Player *newPlayer;
	if (type == "Petani") newPlayer = new Farmer();
	else if (type == "Peternak") newPlayer = new Breeder();
	else if (type == "Walikota") newPlayer = new Mayor();
	else throw InvalidPlayerTypeException();

	newPlayer->username = username;
	newPlayer->weight = weight;
	newPlayer->money = money;
	auto inventorySize = context.miscConfig.getInventorySize();
	newPlayer->inventory = Storage<shared_ptr<Item>>(inventorySize.first, inventorySize.second);

	int inventoryCount;
	inputStream >> inventoryCount;
	while (inventoryCount--) {
		string name;
		inputStream >> name;
		string code = context.itemFactory.getCodeByName(name);
		shared_ptr<Item> item = context.itemFactory.createBaseItem(code);
		newPlayer->inventory.addItem(item);
	}

	if (newPlayer->type == FarmerType) {
		Farmer *farmer = dynamic_cast<Farmer *>(newPlayer);

		auto farmSize = context.miscConfig.getFarmSize();
		farmer->farm = Storage<FarmItem>(farmSize.second, farmSize.first);
		int farmCount;
		inputStream >> farmCount;
		while (farmCount--) {
			int age;
			string location, name;
			inputStream >> location >> name >> age;
			string code = context.itemFactory.getCodeByName(name);
			FarmItem item;
			context.itemFactory.createItem(code, item);
			item.setAge(age);
			farmer->farm.setItem(location, item);
		}
	} else if (newPlayer->type == BreederType) {
		Breeder *breeder = dynamic_cast<Breeder *>(newPlayer);

		auto barnSize = context.miscConfig.getBarnSize();
		breeder->barn = Storage<BarnItem>(barnSize.second, barnSize.first);
		int farmCount;
		inputStream >> farmCount;
		while (farmCount--) {
			int weight;
			string location, name;
			inputStream >> location >> name >> weight;
			string code = context.itemFactory.getCodeByName(name);
			BarnItem item;
			context.itemFactory.createItem(code, item);
			item.setWeight(weight);
			breeder->barn.setItem(location, item);
		}
	}

	shared_ptr<Player> ptr{newPlayer};
	return ptr;
};
