#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "GameObject.hpp"
#include "Player.hpp"

class PlayerController : public GameObject {
	friend GameContext;

protected:
	PlayerController();
	vector<Heapify<Player>> players;
	vector<Player *> ordered;

public:
	void addPlayer(Heapify<Player> &player);
	void rearrangePosition();
	vector<Player *> *getPlayers();
};

#endif
