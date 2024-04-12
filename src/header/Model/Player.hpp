#ifndef MODEL_PLAYER_HPP
#define MODEL_PLAYER_HPP

#include "Container/Heapify.hpp"
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
	Storage<Heapify<Item>> inventory;

	Player();
	virtual ~Player();
	virtual Player *clone() = 0;

	virtual int calculateTax() = 0;
	int countInventoryWealth();

	static int getTaxBracket(int taxed);
	static string playerTypeToString(int type);
};

#endif
