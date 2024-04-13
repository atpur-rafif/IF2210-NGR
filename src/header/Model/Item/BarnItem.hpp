#ifndef MODEL_ITEM_BARNITEM_HPP
#define MODEL_ITEM_BARNITEM_HPP

#include "Model/Item.hpp"
#include "Controller/GameContext.hpp"

enum BarnItemType {
	Herbivore,
	Carnivore,
	Omnivore
};

class BarnItem : public Item {
private:
	BarnItemType barnItemType;
	int weightToHarvest;
	int currentWeight;
	static int p;
	virtual void readAttributeFromStream(istream &inputStream);

public:
	BarnItem();
	virtual BarnItem *clone() const;
	virtual ~BarnItem();

	int getWeightToHarvest();
	BarnItemType getBarnItemType();
	int getWeight();
	void setWeight(int weight);
};


#endif