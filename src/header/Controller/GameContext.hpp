#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "Controller/ItemFactory.hpp"
#include "Controller/PlayerController.hpp"
#include "Controller/ShopController.hpp"
#include "View/Config/MiscConfig.hpp"

class GameContext {
protected:
	ItemFactory itemFactory;
	MiscConfig miscConfig;
	PlayerController playerController;
	ShopController shopController;

public:
	GameContext();
	ItemFactory &getItemFactory();
	MiscConfig &getMiscConfig();
	PlayerController &getPlayerController();
	ShopController &getShopController();
};

#endif
