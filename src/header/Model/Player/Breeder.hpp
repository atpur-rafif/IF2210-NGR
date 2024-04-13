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

	virtual void readSpecializedConfig(istream &inputStream);
	void writeSpecializedConfig(ostream &outputStream);

	void placeAnimal(string &, string &);
	void giveFood(string &, string &);
	void giveFoodChecker(string &);
	void harvestAnimal(string &);
};

#endif
