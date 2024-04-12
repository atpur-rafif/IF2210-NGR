#ifndef SHOP_ITEM_HPP
#define SHOP_ITEM_HPP

#include "PlayerView.hpp"
#include <iostream>
#include <map>
#include <string>
using namespace std;

class Shop : public PlayerView {

public:
  map<string, int> shopInventory{// Plant
                                 {"TEK", -1},
                                 {"SDT", -1},
                                 {"ALT", -1},
                                 {"IRN", -1},
                                 {"APL", -1},
                                 {"ORG", -1},
                                 {"BNT", -1},
                                 {"GAV", -1},

                                 // Animal
                                 {"COW", -1},
                                 {"SHP", -1},
                                 {"HRS", -1},
                                 {"RBT", -1},
                                 {"SNK", -1},
                                 {"CHK", -1},
                                 {"DCK", -1},

                                 // Product
                                 {"TAW", 0},
                                 {"SAW", 0},
                                 {"ALW", 0},
                                 {"IRW", 0},
                                 {"APP", 0},
                                 {"ORP", 0},
                                 {"BNP", 0},
                                 {"GAP", 0},
                                 {"COM", 0},
                                 {"SHM", 0},
                                 {"HRM", 0},
                                 {"RBM", 0},
                                 {"SNM", 0},
                                 {"CHM", 0},
                                 {"DCM", 0},
                                 {"CHE", 0},
                                 {"DCE", 0},

                                 // Building Recipe
                                 {"SMH", 0},
                                 {"MDH", 0},
                                 {"LRH", 0},
                                 {"HTL", 0}};

  template <class T> void sellItem(Player &player);

  template <class T> void buyItem(Player &player);
};

#endif
