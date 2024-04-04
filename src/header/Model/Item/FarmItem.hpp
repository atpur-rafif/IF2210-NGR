#ifndef MODEL_ITEM_FARMITEM_HPP
#define MODEL_ITEM_FARMITEM_HPP

#include "Model/Item.hpp"

enum FarmItemType {
	Material,
	Fruit
};

class FarmItem : public Item {
private:
	FarmItemType farmItemType;
	int durationToHarvest;
	int currentAge;
	virtual void readAttributeFromStream(istream &inputStream);

public:
	FarmItem();
	virtual FarmItem *clone() const;
	virtual ~FarmItem();

	int getDurationToHarvest();
	FarmItemType getFarmItemType();
	int getAge();
	void setAge(int age);
};

#endif
