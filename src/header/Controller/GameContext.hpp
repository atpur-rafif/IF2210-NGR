#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "Controller/ItemFactory.hpp"
#include "Controller/PlayerController.hpp"
#include "View/Config/MiscConfig.hpp"

class GameContext {
public:
	int id;
	GameContext();
	ItemFactory itemFactory;
	MiscConfig miscConfig;
	PlayerController players;
};

#endif
