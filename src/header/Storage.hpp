#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "Item.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Storage {
private:
	vector<Item *> storage;

public:
	Item &getItem(char x, int y);
	friend ostream &operator<<(ostream &, Storage);
};

class Inventory : public Storage {};
class Barn : public Storage {};
class Farm : public Storage {};

#endif
