#include "Model/GameObject.hpp"

GameContext &GameObject::getContext() const { return *this->context; }
void GameObject::setContext(GameContext &ctx) { this->context = &ctx; }
