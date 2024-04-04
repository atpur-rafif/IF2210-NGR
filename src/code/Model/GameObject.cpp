#include "Model/GameObject.hpp"

#include <iostream>
using namespace std;

GameContext &GameObject::getContext() const { return *this->context; }
void GameObject::setContext(GameContext &ctx) { this->context = &ctx; }
