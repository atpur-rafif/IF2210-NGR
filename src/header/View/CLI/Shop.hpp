#ifndef SHOP_ITEM_HPP
#define SHOP_ITEM_HPP

#include "PlayerView.hpp"
#include <iostream>
#include <string>
using namespace std;

class Shop : public PlayerView {
    
public:
    template <class T>
    void sellItem(Player &player);

    template <class T>
    void buyItem(Player &player);
};

#endif