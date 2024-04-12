#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "Model/GameObject.hpp"
#include "Model/Player.hpp"

class PlayerController : public GameObject {
	friend GameContext;

protected:
	PlayerController();
	vector<Heapify<Player>> players;
	vector<Player *> ordered;
	int currentPlayerIndex;

public:
	void nextPlayer();
	Player &getCurrentPlayer();
	void addPlayer(Heapify<Player> &player);
	void rearrangePosition();
	vector<Player *> *getPlayers();
	Heapify<Player> readPlayerFromStream(istream &inputStream);
};

#endif