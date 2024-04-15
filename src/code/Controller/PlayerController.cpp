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
		return a->getUsername() < b->getUsername() || PlayerController::toLower(a->getUsername()) < PlayerController::toLower(b->getUsername());
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

	for (const auto &element : context.getPlayerController().getPlayers()) {
		if (element->getUsername() == username) throw GameException("Username \"" + username + "\" already exist");
	}

	Player *newPlayer;
	if (type == "Petani") newPlayer = new Farmer();
	else if (type == "Peternak") newPlayer = new Breeder();
	else if (type == "Walikota") newPlayer = new Mayor();
	else throw GameException("Invalid player type \"" + type + "\" found");

	newPlayer->setContext(this->getContext());
	newPlayer->setUsername(username);
	newPlayer->setWeight(weight);
	newPlayer->setMoney(money);
	newPlayer->readInventory(inputStream);
	newPlayer->readSpecializedConfig(inputStream);
	shared_ptr<Player> ptr{newPlayer};
	return ptr;
};

void PlayerController::writePlayerToStream(shared_ptr<Player> player, ostream &outputStream) {
	outputStream << player->getUsername() << ' ';
	outputStream << Player::playerTypeToString(player->getType()) << ' ';
	outputStream << player->getWeight() << ' ';
	outputStream << player->getMoney() << endl;
	player->writeInventory(outputStream);
};
