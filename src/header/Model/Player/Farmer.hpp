#ifndef MODEL_PLAYER_FARMER_HPP
#define MODEL_PLAYER_FARMER_HPP

#include "Model/Item/FarmItem.hpp"
#include "Model/Player.hpp"
#include "Controller/ItemFactory.hpp"
#include "Controller/GameContext.hpp"

class Farmer : public Player {
public:
	Storage<FarmItem> farm; // Ladang

	Farmer();
	virtual Farmer *clone();
	virtual ~Farmer(); 

	virtual int calculateTax();
	int countFarmWealth();
	void cetakLadang();
	void plant(string &invLocation, string &fieldLocation);
	void harvestPlant(string &coordinate);
	void printFieldDetail();
};

#endif
