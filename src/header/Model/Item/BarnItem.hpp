#ifndef MODEL_ITEM_BARNITEM_HPP
#define MODEL_ITEM_BARNITEM_HPP

#include "Controller/GameContext.hpp"
#include "Model/Harvestable.hpp"
#include "Model/Item.hpp"

enum BarnItemType {
	Herbivore,
	Carnivore,
	Omnivore
};

class BarnItem : public Harvestable {
private:
	BarnItemType barnItemType;
	int weightToHarvest;
	int currentWeight;
	virtual void readAttributeFromStream(istream &inputStream);

public:
	BarnItem();
	virtual BarnItem *clone() const;
	virtual ~BarnItem();

	int getWeightToHarvest();
	BarnItemType getBarnItemType();
	int getWeight();
	void setWeight(int weight);

	bool harvestable();
	void readHarvestState(istream &inputStream);
	void writeHarvestState(ostream &outputStream);
};

#endif
