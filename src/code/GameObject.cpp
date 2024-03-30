#include "GameObject.hpp"

GameContext &GameObject::getContext() { return *this->context; }
void GameObject::setContext(GameContext &context) { this->context = &context; }
