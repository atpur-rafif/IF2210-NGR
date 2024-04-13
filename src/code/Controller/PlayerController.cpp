#include "Controller/PlayerController.hpp"
#include "Controller/GameContext.hpp"
#include "Model/Player/Breeder.hpp"
#include "Model/Player/Farmer.hpp"
#include "Model/Player/Mayor.hpp"
#include <algorithm>
#include <string>

PlayerController::PlayerController() {
	this->currentPlayerIndex = 0;
}

string PlayerController::toLower(string textInput) {
	string text = "";
	text += textInput;
	transform(text.begin(), text.end(), text.begin(), ::tolower);
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
		return a->username < b->username || PlayerController::toLower(a->username) < PlayerController::toLower(b->username);
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

	for (const auto &element : context.players.getPlayers()) {
		if (element->username == username) throw "Username already exist";
	}

	Player *newPlayer;
	if (type == "Petani") newPlayer = new Farmer();
	else if (type == "Peternak") newPlayer = new Breeder();
	else if (type == "Walikota") newPlayer = new Mayor();
	else throw "Invalid player type";

	newPlayer->setContext(this->getContext());
	newPlayer->username = username;
	newPlayer->weight = weight;
	newPlayer->money = money;
	newPlayer->readInventory(inputStream);
	newPlayer->readSpecializedConfig(inputStream);

	shared_ptr<Player> ptr{newPlayer};
	return ptr;
};

void PlayerController::writePlayerToStream(shared_ptr<Player> player, ostream &outputStream) {
	outputStream << player->username << ' ';
	outputStream << Player::playerTypeToString(player->type) << ' ';
	outputStream << player->weight << ' ';
	outputStream << player->money << endl;
	player->writeInventory(outputStream);
};
