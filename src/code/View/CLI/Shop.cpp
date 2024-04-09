#include "View/CLI/Shop.hpp"
#include "Model/Item/ProductItem.hpp"

#include <iostream>
using namespace std;

template <class T> void Shop::sellItem(Player &player) {
  ProductItem *product;
  cout << "Berikut merupakan penyimpanan Anda\n     ================[ "
          "Penyimpanan ]==================\n";
  PlayerView::printInventory(player);
  cout << "Silahkan pilih petak yang ingin Anda jual!\nPetak : ";
  string location;
  cin >> location;
  if (location == "CANCEL")
    throw UserCancelledPlayerViewException();
  try {
    auto rawItem = player.inventory.getItem(location);
    if (!rawItem.has_value()) {
      cout << "Tidak ada item pada lokasi ini!\n";
    }

    T *casted = dynamic_cast<T *>(rawItem->getRaw());
    if (casted == NULL) {
      cout << "Invalid item type\n";
    };

    *product = *casted;
    player.weight -= product->getAddedWeight();
    player.money += product->getPrice();
    player.inventory.clearItem(location);
  } catch (const exception &err) {
    cout << err.what() << endl;
  }
}

template <class T> void Shop::buyItem(Player &player) {}
