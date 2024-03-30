#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "GameObject.hpp"
#include "Player.hpp"

class PlayerController : public GameObject {
private:
	vector<Player> players;
	void rearrangePosition();

public:
	void addPlayer(Player player);
	vector<Player> *getPlayers();
};

#endif
