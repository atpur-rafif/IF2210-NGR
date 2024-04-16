#ifndef SHOP_CONTROLLER_HPP
#define SHOP_CONTROLLER_HPP

#include "Model/GameObject.hpp"
#include "Model/Item.hpp"
#include "Model/Player.hpp"
#include <map>
#include <set>
#include <string>
using namespace std;

class ShopController : public GameObject {
protected:
	static map<ItemType, bool> infinity;
	static map<PlayerType, set<ItemType>> catalogue;
	static map<PlayerType, set<ItemType>> accept;
	map<string, int> items;

public:
	map<string, int> getCatalogue(PlayerType type);
	bool getAccepted(PlayerType playerType, ItemType itemType);
	void addItem(shared_ptr<Item> &item);
	void addItem(shared_ptr<Item> &item, int count);
	void removeItem(shared_ptr<Item> &item);
	void removeItem(shared_ptr<Item> &item, int count);

	void readShopFromStream(istream &inputStream);
	void writeShopToStream(ostream &outputStream);
};

#endif
