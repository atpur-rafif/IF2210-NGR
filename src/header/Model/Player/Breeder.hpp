#ifndef MODEL_PLAYER_BREEDER_HPP
#define MODEL_PLAYER_BREEDER_HPP

#include "Model/Item/BarnItem.hpp"
#include "Model/Player.hpp"

class Breeder : public Player {

public:
	Storage<BarnItem> barn;
	
	Breeder();
	virtual Breeder *clone();
	virtual ~Breeder();

	virtual int calculateTax();
	int countBarnWealth();

	//function build by me
	void placeAnimal(); 
	void giveFood(string&, string&);
	void harvestAnimal(string&);
};

#endif
