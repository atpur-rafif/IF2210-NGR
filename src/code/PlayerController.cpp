#include "PlayerController.hpp"
#include <algorithm>

PlayerController::PlayerController() {}

void PlayerController::rearrangePosition() {
	int size = this->players.size();
	this->ordered.resize(size);
	for (int i = 0; i < size; ++i)
		this->ordered[i] = this->players[i].getRaw();

	// auto begin = this->ordered.begin();
	// auto end = begin + this->ordered.size();
	//
	// sort(begin, end, [](Player *a, Player *b) {
	// 	return a->getUsername() < b->getUsername();
	// });
}

void PlayerController::addPlayer(Heapify<Player> &player) {
	this->players.push_back(player);
	this->rearrangePosition();
};

vector<Player *> *PlayerController::getPlayers() {
	return &(this->ordered);
}
