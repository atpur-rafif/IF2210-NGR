#ifndef MODEL_ITEM_HPP
#define MODEL_ITEM_HPP

#include "Model/GameObject.hpp"
#include <iostream>
#include <string>
using namespace std;

enum ItemType {
	Product,
	Farm,
	Barn,
	Building
};

class Item : virtual public GameObject {
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

#endif
