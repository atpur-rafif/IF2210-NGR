#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include "Model/GameObject.hpp"
#include "Model/Player.hpp"

class PlayerController : public GameObject {
	friend GameContext;

protected:
	PlayerController();
	vector<shared_ptr<Player>> players;
	int currentPlayerIndex;

public:
	void nextPlayer();
	shared_ptr<Player> getCurrentPlayer();
	void addPlayer(shared_ptr<Player> player);
	void rearrangePosition();
	vector<shared_ptr<Player>> getPlayers();
	shared_ptr<Player> readPlayerFromStream(istream &inputStream);
	static string toLower(string text);
};

#endif