#ifndef MODEL_PLAYER_BREEDER_HPP
#define MODEL_PLAYER_BREEDER_HPP

#include "Model/Item/BarnItem.hpp"
#include "Model/Item/ProductItem.hpp"
#include "Controller/ItemFactory.hpp"
#include "Controller/GameContext.hpp"
#include "Model/Player.hpp"
#include "Exception/StorageException.hpp"
#include "Exception/DowncastException.hpp"

class ProductItem;

class Breeder : public Player {

public:
	Storage<BarnItem> barn;
	
	Breeder();
	virtual Breeder *clone();
	virtual ~Breeder();

	virtual int calculateTax();
	int countBarnWealth();

	//function build by me
	void placeAnimal(string&, string&); 
	void giveFood(string&, string&);
	void harvestAnimal(string&);
};

#endif