#ifndef MODEL_PLAYER_BREEDER_HPP
#define MODEL_PLAYER_BREEDER_HPP

#include "Model/Harvester.hpp"
#include "Model/Item/BarnItem.hpp"
#include "Model/Player.hpp"

class Breeder : public Harvester<BarnItem> {
public:
	Breeder();
	virtual Breeder *clone();
	virtual ~Breeder();

	int calculateTax();
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
