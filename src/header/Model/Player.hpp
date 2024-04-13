#ifndef MODEL_PLAYER_HPP
#define MODEL_PLAYER_HPP

#include "Container/Storage.hpp"
#include "Model/GameObject.hpp"
#include "Model/Item.hpp"
#include <memory>

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
	Storage<shared_ptr<Item>> inventory;

	Player();
	virtual ~Player();
	virtual Player *clone() = 0;

	virtual int calculateTax() = 0;
	int countInventoryWealth();

	static int getTaxBracket(int taxed);
	static string playerTypeToString(int type);

	void readInventory(istream &inputStream);
	void writeInventory(ostream &outputStream);
	virtual void readSpecializedConfig(istream &inputStream) = 0;
	virtual void writeSpecializedConfig(ostream &outputStream) = 0;
};

#endif
