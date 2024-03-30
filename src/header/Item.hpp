#ifndef ITEM_HPP
#define ITEM_HPP

#include "GameObject.hpp"
#include <iostream>
#include <map>
using namespace std;

enum ItemType {
	Product,
	Farm,
	Barn,
	Building
};

class Item : public GameObject {
protected:
	int price;
	int id;
	string code;
	string name;
	ItemType type;
	virtual void readAttributeFromStream(istream &inputStream) = 0;

public:
	Item();
	virtual Item *clone() const = 0;
	virtual ~Item();

	int getPrice();
	int getId();
	string getCode();
	string getName();
	ItemType getType();

	friend istream &operator>>(istream &inputStream, Item &item);
};

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

class BuildingItem : public Item {
private:
	map<string, int> building;
	virtual void readAttributeFromStream(istream &inputStream);

public:
	BuildingItem();
	virtual BuildingItem *clone() const;
	virtual ~BuildingItem();

	map<string, int> *getIngredients();

	friend istream &operator>>(istream &inputStream, BuildingItem &item);
};

#endif
