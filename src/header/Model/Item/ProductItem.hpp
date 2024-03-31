#ifndef MODEL_ITEM_PRODUCTITEM_HPP
#define MODEL_ITEM_PRODUCTITEM_HPP

#include "Model/Item.hpp"

enum ProductItemType {
	MaterialPlant,
	FruitPlant,
	Animal
};

class ProductItem : public Item {
private:
	string origin;
	int addedWeight;
	ProductItemType productItemType;
	virtual void readAttributeFromStream(istream &inputStream);

public:
	ProductItem();
	virtual ProductItem *clone() const;
	virtual ~ProductItem();

	ProductItemType getProductItemType();
};

#endif
