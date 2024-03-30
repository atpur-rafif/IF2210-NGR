#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "Heapify.hpp"
#include "Player.hpp"

class PlayerController {
private:
	vector<Heapify<Player>> players;
	void rearrangePosition();

public:
	void addPlayer(Heapify<Player> player);
	vector<Heapify<Player>> *getPlayers();
};

#endif
