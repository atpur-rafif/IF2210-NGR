#ifndef MODEL_PLAYER_BREEDER_HPP
#define MODEL_PLAYER_BREEDER_HPP

#include "Model/Item/BarnItem.hpp"
#include "Model/Player.hpp"

class Breeder : public Player {
protected:
	Storage<BarnItem> barn;

public:
	Breeder();
	virtual Breeder *clone();
	virtual ~Breeder();

	Storage<BarnItem> &getBarn();

	virtual int calculateTax();
	int countBarnWealth();

	virtual void readSpecializedConfig(istream &inputStream);
	void writeSpecializedConfig(ostream &outputStream);

	void placeAnimal(string &, string &);
	void giveFood(string &, string &);
	bool hasProductToFeed(BarnItemType type);
	void harvestAnimal(string &);

	static bool ableToFeed(BarnItemType animal, ProductItemType product);
};

#endif
