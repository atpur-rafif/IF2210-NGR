#include "Controller/GameContext.hpp"
#include <cstdlib>

GameContext::GameContext() {
	this->id = rand();
	this->itemFactory.setContext(*this);
	this->players.setContext(*this);
}
