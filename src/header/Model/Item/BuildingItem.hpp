#ifndef MODEL_ITEM_BUILDINGITEM_HPP
#define MODEL_ITEM_BUILDINGITEM_HPP

#include "Model/Item.hpp"
#include <map>

class BuildingItem : public Item {
private:
	map<string, int> building;
	virtual void readAttributeFromStream(istream &inputStream);

public:
	BuildingItem();
	virtual BuildingItem *clone() const;
	virtual ~BuildingItem();

	map<string, int> &getIngredients();

	friend istream &operator>>(istream &inputStream, BuildingItem &item);
};

#endif
