#include "Controller/PlayerController.hpp"
#include "Controller/GameContext.hpp"
#include "Exception/GameException.hpp"
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

void PlayerController::checkWinner() {
	auto &miscConfig = this->getContext().getMiscConfig();
	for (auto &player : this->getPlayers()) {
		if (player->getMoney() >= miscConfig.getTargetMoney() && player->getWeight() >= miscConfig.getTargetWeight()) {
			throw EndGameException("=== Selamat, pemain " + player->getUsername() + " menang ===");
		}
	}
};

void PlayerController::nextPlayer() {
	this->currentPlayerIndex = (this->currentPlayerIndex + 1) % this->players.size();
}

shared_ptr<Player> PlayerController::getCurrentPlayer() {
	return this->players.at(this->currentPlayerIndex);
};

bool PlayerController::validateNewUsername(string name) {
	for (auto &player : this->players)
		if (player->getUsername() == name) return false;
	return true;
};

bool PlayerController::hasMayor() { return this->mayor; }

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
	if (player->getType() == MayorType) this->mayor = true;
	this->rearrangePosition();
};

vector<shared_ptr<Player>> PlayerController::getPlayers() {
	return this->players;
}

shared_ptr<Player> PlayerController::readPlayerFromStream(istream &inputStream) {
	int weight, money;
	string username, typeString;
	inputStream >> username >> typeString >> weight >> money;

	if (!this->validateNewUsername(username))
		throw GameException("Username \"" + username + "\" already exist");

	auto opt = Player::stringToPlayerType(typeString);
	if (!opt.has_value())
		throw GameException("Invalid player type");

	auto type = opt.value();
	Player *newPlayer = nullptr;
	if (type == FarmerType) newPlayer = new Farmer();
	else if (type == BreederType) newPlayer = new Breeder();
	else if (type == MayorType) newPlayer = new Mayor();

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
