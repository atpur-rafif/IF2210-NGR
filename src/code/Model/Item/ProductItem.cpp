#include "Model/Item/ProductItem.hpp"

ProductItem::ProductItem() { this->type = Product; }
ProductItem::ProductItem(string origin, int weight, ProductItemType itemType) {
	this->type = Product;
	this->origin = origin;
	this->addedWeight = weight;
	this->productItemType = itemType;
}
ProductItem::~ProductItem() {}
ProductItem *ProductItem::clone() const { return new ProductItem(*this); }

ProductItemType ProductItem::getProductItemType() { return this->productItemType; }

int ProductItem::getAddedWeight() {
	return this->addedWeight;
};

void ProductItem::readAttributeFromStream(istream &inputStream) {
	string type;
	inputStream >> type;
	if (type == "PRODUCT_MATERIAL_PLANT") this->productItemType = MaterialProduct;
	else if (type == "PRODUCT_FRUIT_PLANT") this->productItemType = MaterialProduct;
	else if (type == "PRODUCT_ANIMAL") this->productItemType = AnimalProduct;

	inputStream >> this->origin;
	inputStream >> this->addedWeight;
}

string ProductItem::getOrigin() {
	return this->origin;
}
