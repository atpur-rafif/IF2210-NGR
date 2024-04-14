#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "Controller/ItemFactory.hpp"
#include "Controller/PlayerController.hpp"
#include "View/Config/MiscConfig.hpp"

class GameContext {
protected:
	ItemFactory itemFactory;
	MiscConfig miscConfig;
	PlayerController playerController;

public:
	GameContext();
	ItemFactory &getItemFactory();
	MiscConfig &getMiscConfig();
	PlayerController &getPlayerController();
};

#endif
