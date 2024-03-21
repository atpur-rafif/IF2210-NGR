#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
using namespace std;

class Item {
private:
	int price;

public:
	Item(int price);
	int getPrice();
};

enum InventoryItemType {
	MaterialPlant,
	FruitPlant,
	Animal
};

class InventoryItem : public Item {
private:
	InventoryItemType type;

public:
	InventoryItem(int price);
	InventoryItemType getType();
	friend istream &operator<<(istream &inputStream, InventoryItem item);
};

enum FarmItemType {
	Material,
	Fruit
};

class FarmItem : public Item {
private:
	FarmItemType type;
	int durationToHarvest;

public:
	FarmItem(int price, int durationToHarvest);
	int getDurationToHarvest();
	FarmItemType getType();
	friend istream &operator<<(istream &inputStream, FarmItem item);
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

public:
	BarnItem(int price, int weightToHarvest);
	int getWeightToHarvest();
	BarnItemType getType();
	friend istream &operator<<(istream &inputStream, BarnItem item);
};

#endif
