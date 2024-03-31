#ifndef MODEL_PLAYER_FARMER_HPP
#define MODEL_PLAYER_FARMER_HPP

#include "Model/Item/FarmItem.hpp"
#include "Model/Player.hpp"

class Farmer : public Player {
public:
	Storage<FarmItem> farm;

	Farmer();
	virtual Farmer *clone();
	virtual ~Farmer();

	virtual int calculateTax();
	int countFarmWealth();
};

#endif
