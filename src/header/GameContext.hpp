#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "ItemFactory.hpp"
#include "MiscConfig.hpp"
#include "PlayerController.hpp"

class GameContext {
public:
	int id;
	GameContext();
	ItemFactory itemFactory;
	MiscConfig miscConfig;
	PlayerController players;
};

#endif
