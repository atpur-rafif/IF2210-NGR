#include "PlayerController.hpp"

void PlayerController::addPlayer(Player player) {
	this->players.push_back(player);
}

vector<Player> *PlayerController::getPlayers() {
	return &(this->players);
}
