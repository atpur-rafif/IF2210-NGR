#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <map>
using namespace std;

template <class T>
class ItemFactory {
private:
	map<int, T> repository;

public:
	void addItem(T item) {
		this->repository[item.getId()] = item;
	}
	int getIdByName(string name) {
		for (auto const &i : this->repository) {
			auto item = i.second;
			if (item.getName() == name) {
				return item.getId();
			}
		}
		return -1;
	};
	int getIdByCode(string code) {
		for (auto const &i : this->repository) {
			auto item = i.second;
			if (item.getName() == code) {
				return item.getId();
			}
		}
		return -1;
	}
	T createItemById(int id) {
		return repository[id];
	};
};

enum ItemType {
	Product,
	Farm,
	Barn,
	Building
};

class Item {
protected:
	template <class T>
	friend class ItemFactory;
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
	ProductItem(int price);
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
	FarmItem(int price, int durationToHarvest);
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
	BarnItem(int price, int weightToHarvest);
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
