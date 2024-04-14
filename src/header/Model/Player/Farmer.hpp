#ifndef MODEL_PLAYER_FARMER_HPP
#define MODEL_PLAYER_FARMER_HPP

#include "Controller/GameContext.hpp"
#include "Controller/ItemFactory.hpp"
#include "Exception/DowncastException.hpp"
#include "Exception/ItemFactoryException.hpp"
#include "Exception/StorageException.hpp"
#include "Model/GameObject.hpp"
#include "Model/Item/FarmItem.hpp"
#include "Model/Item/ProductItem.hpp"
#include "Model/Player.hpp"

class ProductItem;

class Farmer : public Player {
protected:
	Storage<FarmItem> farm;

public:
	Farmer();
	virtual Farmer *clone();
	virtual ~Farmer();

	Storage<FarmItem> &getFarm();

	virtual int calculateTax();
	int countFarmWealth();

	virtual void readSpecializedConfig(istream &inputStream);
	virtual void writeSpecializedConfig(ostream &outputStream);
	void plant(string &invLocation, string &fieldLocation);
	void harvestPlant(string &coordinate);
	void plantsGrow();
};

#endif
