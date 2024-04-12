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

        T *casted = dynamic_cast<T *>(rawItem);
        if (casted == NULL) {
            cout << "Invalid item type\n";
        };

        ProductItem *product = casted;
        if ((product->getType() == 3) && (player.type == 0 || player.type == 1)) {
            throw 
        }

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
    vector<shared_ptr<Item> *> vec = player.inventory.getAllItem();
    this->printInventory(shopInventory);
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

void Shop::printInventory(const map<string, int> &m) {
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
