#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "Item.hpp"
#include "Storage.hpp"

class GameContext;

enum PlayerType {
	FarmerType,
	BreederType,
	MayorType
};

class Player : public GameObject {
public:
	string username;
	PlayerType type;
	int weight;
	int money;
	HeapifyStorage<Item> inventory;

	Player();
	virtual ~Player();
	virtual Player *clone();
};

class Farmer : public Player {
public:
	Storage<FarmItem> farm;

	Farmer();
	virtual Farmer *clone();
	virtual ~Farmer();
};

class Breeder : public Player {
public:
	Storage<BarnItem> barn;

	Breeder();
	virtual Breeder *clone();
	virtual ~Breeder();
};

class Mayor : public Player {
public:
	Mayor();
	virtual Mayor *clone();
	virtual ~Mayor();
};

#endif
