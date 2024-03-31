#ifndef MODEL_PLAYER_HPP
#define MODEL_PLAYER_HPP

#include "Container/Storage.hpp"
#include "Model/GameObject.hpp"
#include "Model/Item.hpp"

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
	virtual Player *clone() = 0;

	virtual int calculateTax() = 0;
	int countInventoryWealth();

	static int getTaxBracket(int taxed);
};

#endif
