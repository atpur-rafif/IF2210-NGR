#include "PlayerController.hpp"

void PlayerController::addPlayer(Player player) {
	this->players.push_back(player);
	this->players[this->players.size() - 1].setContext(this->getContext());
}

vector<Player> *PlayerController::getPlayers() {
	return &(this->players);
}
