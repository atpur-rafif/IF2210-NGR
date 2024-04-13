#ifndef SHOP_ITEM_HPP
#define SHOP_ITEM_HPP

#include "Controller/ItemFactory.hpp"
#include "PlayerView.hpp"
#include <map>
#include <string>
using namespace std;

class Shop : public PlayerView {
public:
    ItemFactory itemFactory;
    /*
    * Map item's code to the amount of that item
    * -1 to indicate infinite amount of that item
    **/
    map<string, int> shopInventory;

    void initShopInventory();

    pair<string, int> nthItem(int n);

    template <class T>
    void playerSellItem(Player &player);

	void playerBuyItem(Player &player);

    void printShopInventory();
};

#endif
