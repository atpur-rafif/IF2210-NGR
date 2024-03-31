#include "Player.hpp"
#include "GameContext.hpp"

Player::Player() {}
Farmer::Farmer() { this->type = FarmerType; }
Breeder::Breeder() { this->type = BreederType; }
Mayor::Mayor() { this->type = MayorType; }

Player::~Player() {}
Farmer::~Farmer() {}
Breeder::~Breeder() {}
Mayor::~Mayor() {}

Player *Player::clone() { return new Player(*this); }
Farmer *Farmer::clone() { return new Farmer(*this); }
Breeder *Breeder::clone() { return new Breeder(*this); }
Mayor *Mayor::clone() { return new Mayor(*this); }
