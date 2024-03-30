#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "Player.hpp"

class PlayerController {
private:
	vector<Player> players;
	void rearrangePosition();

public:
	void addPlayer(Player player);
	vector<Player> *getPlayers();
};

#endif
