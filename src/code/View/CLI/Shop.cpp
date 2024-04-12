#include "View/CLI/Shop.hpp"
#include "Model/Item/ProductItem.hpp"

#include <iostream>
using namespace std;

template <class T>
void Shop::playerSellItem(Player &player) {
    cout << "Berikut merupakan penyimpanan Anda\n     ================[ Penyimpanan ]==================\n";
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

        ProductItem *product = casted;
        if (shopInventory[product->getCode()] != -1)
            shopInventory[product->getCode()]++;
        
        player.weight -= product->getAddedWeight();
        player.money += product->getPrice();
        player.inventory.clearItem(location);
    } catch (const exception &err) {
        cout << err.what() << endl;
    }
}

template <class T>
void Shop::playerBuyItem(Player &player) {
    vector<Heapify<Item>> vec;
    player.inventory.getAllItem(&vec)
    this->printInventory();
    pair<int, int> size = player.inventory.getSize();
    cout << "\nUang Anda : " << player.money <<
    "\nSlot penyimpanan tersedia : " << (size.first * size.second) - vec.size() <<
    "\nBarang ingin dibeli : ";
    int select, qty;
    cin >> select;
    cout << "\nKuantitas : ";
    cin >> qty;

    // CONTINUE



}

void Shop::printInventory(map<string, int> &m) {
    cout << "Selamat datang di toko!!\nBerikut merupakan hal yang dapat Anda Beli\n";
    int i = 0;
    for(const auto& [key, value] : m) {
        if (value != 0) {
            cout << i << ". " << key << " - " << "price" << " (" << "quantity" << ")\n";
            ++i;
        }
        else if(value == -1) {
            cout << i << ". " << key << " - " << "price\n";
            ++i;
        }
    }
}
