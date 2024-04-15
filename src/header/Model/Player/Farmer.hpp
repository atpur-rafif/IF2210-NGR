#ifndef MODEL_PLAYER_FARMER_HPP
#define MODEL_PLAYER_FARMER_HPP

#include "Controller/GameContext.hpp"
#include "Controller/ItemFactory.hpp"
#include "Exception/StorageException.hpp"
#include "Model/GameObject.hpp"
#include "Model/Harvester.hpp"
#include "Model/Item/FarmItem.hpp"
#include "Model/Item/ProductItem.hpp"
#include "Model/Player.hpp"

class ProductItem;

class Farmer : public Harvester<FarmItem> {
public:
	Farmer();
	virtual Farmer *clone();
	virtual ~Farmer();

	int calculateTax();
	int countFarmWealth();

	virtual void readSpecializedConfig(istream &inputStream);
	virtual void writeSpecializedConfig(ostream &outputStream);
	void plant(string &invLocation, string &fieldLocation);
	void harvestPlant(string &coordinate);
	void plantsGrow();
};

#endif
