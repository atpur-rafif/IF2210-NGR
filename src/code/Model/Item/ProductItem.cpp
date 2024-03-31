#include "Model/Item/ProductItem.hpp"

ProductItem::ProductItem() { this->type = Product; }
ProductItem::~ProductItem() {}
ProductItem *ProductItem::clone() const { return new ProductItem(*this); }

ProductItemType ProductItem::getProductItemType() { return this->productItemType; }

void ProductItem::readAttributeFromStream(istream &inputStream) {
	string type;
	inputStream >> type;
	if (type == "PRODUCT_MATERIAL_PLANT") this->productItemType = MaterialPlant;
	else if (type == "PRODUCT_FRUIT_PLANT") this->productItemType = MaterialPlant;
	else if (type == "PRODUCT_ANIMAL") this->productItemType = Animal;

	inputStream >> this->origin;
	inputStream >> this->addedWeight;
}
