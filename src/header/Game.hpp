#ifndef GAME_HPP
#define GAME_HPP

#include "ItemFactory.hpp"
#include "MiscConfig.hpp"
#include "PlayerController.hpp"

class GameContext {
public:
	ItemFactory itemFactory;
	MiscConfig miscConfig;
	PlayerController players;
};

class Game {
private:
public:
	Game();
};

#endif
