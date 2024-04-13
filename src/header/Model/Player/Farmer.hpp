#ifndef MODEL_PLAYER_FARMER_HPP
#define MODEL_PLAYER_FARMER_HPP

#include "Model/Item/FarmItem.hpp"
#include "Model/Item/ProductItem.hpp"
#include "Controller/ItemFactory.hpp"
#include "Controller/GameContext.hpp"
#include "Model/Player.hpp"
#include "Model/GameObject.hpp"
#include "Exception/StorageException.hpp"
#include "Exception/DowncastException.hpp"

class ProductItem;

class Farmer : public Player {
public:
	Storage<FarmItem> farm;

	Farmer();
	virtual Farmer *clone();
	virtual ~Farmer();

	virtual int calculateTax();
	int countFarmWealth();
	void plant(string &invLocation, string &fieldLocation);
	void harvestPlant(string &coordinate);
};

#endif
