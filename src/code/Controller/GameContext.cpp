#include "Controller/GameContext.hpp"
#include <cstdlib>

GameContext::GameContext() {
	this->getItemFactory().setContext(*this);
	this->getPlayerController().setContext(*this);
	this->getShopController().setContext(*this);
}

ItemFactory &GameContext::getItemFactory() { return this->itemFactory; };
MiscConfig &GameContext::getMiscConfig() { return this->miscConfig; };
PlayerController &GameContext::getPlayerController() { return this->playerController; };
ShopController &GameContext::getShopController() { return this->shopController; };
