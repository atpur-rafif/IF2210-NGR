#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <map>
using namespace std;

class Item {
protected:
	int price;
	int id;
	string code;
	string name;
	virtual void readAttributeFromStream(istream &inputStream) = 0;

public:
	int getPrice();
	int getId();
	string getCode();
	string getName();
	friend istream &operator>>(istream &inputStream, Item &item);
};

enum InventoryItemType {
	MaterialPlant,
	FruitPlant,
	Animal
};

class InventoryItem : public Item {
private:
	string origin;
	int addedWeight;
	InventoryItemType type;
	virtual void readAttributeFromStream(istream &inputStream);

public:
	InventoryItem();
	virtual ~InventoryItem();
	InventoryItem(int price);
	InventoryItemType getType();
};

enum FarmItemType {
	Material,
	Fruit
};

class FarmItem : public Item {
private:
	FarmItemType type;
	int durationToHarvest;
	virtual void readAttributeFromStream(istream &inputStream);

public:
	FarmItem();
	virtual ~FarmItem();
	FarmItem(int price, int durationToHarvest);
	int getDurationToHarvest();
	FarmItemType getType();
};

enum BarnItemType {
	Herbivore,
	Carnivore,
	Omnivore
};

class BarnItem : public Item {
private:
	BarnItemType type;
	int weightToHarvest;
	static int p;
	virtual void readAttributeFromStream(istream &inputStream);

public:
	BarnItem();
	virtual ~BarnItem();
	BarnItem(int price, int weightToHarvest);
	int getWeightToHarvest();
	BarnItemType getType();
};

class RecipeItem : public Item {
private:
	map<string, int> recipe;
	virtual void readAttributeFromStream(istream &inputStream);

public:
	RecipeItem();
	virtual ~RecipeItem();

	map<string, int> *getIngredients();
	friend istream &operator>>(istream &inputStream, RecipeItem &item);
};

#endif
