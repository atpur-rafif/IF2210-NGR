#include "PlayerController.hpp"
#include <algorithm>

PlayerController::PlayerController() {}

void PlayerController::rearrangePosition() {
	int size = this->players.size();
	this->ordered.resize(size);
	for (int i = 0; i < size; ++i)
		this->ordered[i] = &this->players[i];

	auto begin = this->ordered.begin();
	auto end = begin + this->ordered.size();

	sort(begin, end, [](Player *a, Player *b) {
		return a->getUsername() < b->getUsername();
	});
}

Player &PlayerController::createPlayer() {
	this->players.push_back(Player());
	Player *player = &this->players[this->players.size() - 1];
	player->setContext(this->getContext());
	return *player;
};

vector<Player *> *PlayerController::getPlayers() {
	return &(this->ordered);
}
