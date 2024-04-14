#ifndef SHOP_ITEM_HPP
#define SHOP_ITEM_HPP

#include "Controller/ItemFactory.hpp"
#include "PlayerView.hpp"
#include <map>
#include <string>
using namespace std;

class ShopView {
public:
	static void sellItem(Player &player);
	static void buyItem(Player &player);
};

#endif
