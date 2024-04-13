#include "Exception/ShopException.hpp"
#include "Exception/StorageException.hpp"
#include "Model/Item.hpp"
#include "View/CLI/Shop.hpp"
#include <iostream>
using namespace std;

void Shop::initShopInventory() {
    // Plant
    this->shopInventory["TEK"] = -1; this->shopInventory["SDT"] = -1;
    this->shopInventory["ALT"] = -1; this->shopInventory["IRN"] = -1;
    this->shopInventory["APL"] = -1; this->shopInventory["ORG"] = -1;
    this->shopInventory["BNT"] = -1; this->shopInventory["GAV"] = -1;

    // Animal
    this->shopInventory["COW"] = -1; this->shopInventory["SHP"] = -1;
    this->shopInventory["HRS"] = -1; this->shopInventory["RBT"] = -1;
    this->shopInventory["SNK"] = -1; this->shopInventory["CHK"] = -1;
    this->shopInventory["DCK"] = -1;

}


pair<string, int> Shop::nthItem(int n) {
    int i = 0;
    for(const auto& [key, value] : this->shopInventory) {
        if (i == n - 1) {
            return pair(key, value);
        }
        else if (i < n - 1) {
            i++;
        }
    }
    return pair("", 0);
}

template <class T>
void Shop::playerSellItem(Player &player) {
    cout << "Berikut merupakan penyimpanan Anda\n     ================[ Penyimpanan ]==================\n";
    PlayerView::printInventory(player);
    cout << "Silahkan pilih petak yang ingin Anda jual!\nPetak : ";

    try {
        string location;
        cin >> location;
        if (location == "CANCEL") {
            throw UserCancelledPlayerViewException();
        }

        auto rawItem = player.inventory.getItem(location);
        if (!rawItem.has_value()) {
            throw InvalidItemNotFoundException();
        }

        shared_ptr<T> casted = dynamic_pointer_cast<T>(rawItem.value());
        if (casted == NULL) {
            throw InvalidTypeValueException();
        }
        
        if ((casted->getType() == 3) && (player.type == 0 || player.type == 1)) {
            throw IllegalSalesException();
        }

        if (shopInventory[casted->getCode()] != -1) {
            shopInventory[casted->getCode()]++;
        }
        
        player.weight -= casted->getAddedWeight();
        player.money += casted->getPrice();
        player.inventory.clearItem(location);

    } catch (const exception &err) {
        cout << err.what() << "\n";
    }
}

void Shop::playerBuyItem(Player &player) {
    vector<shared_ptr<Item> *> vec = player.inventory.getAllItem();
    this->initShopInventory();
    this->printShopInventory();
    int available = (player.inventory.getHeight() * player.inventory.getWidth()) - vec.size();

    cout << "\nUang Anda : " << player.money << "\nSlot penyimpanan tersedia : " <<  available << "\nBarang ingin dibeli : ";

    int select, qty;
    cin >> select;
    cout << "\nKuantitas : ";
    cin >> qty;

    try {
        pair<string, int> item = this->nthItem(select);
        if (item == pair<string, int>("", 0)) {
            throw InvalidSelectionException();
        }

        if (qty > available) {
            throw NotEnoughInventoryException();
        }

        if (qty > item.second) {
            throw NotEnoughItemException();
        }
        
        shared_ptr<Item> rawItem;
        itemFactory.createItem(item.first, rawItem);
        if ((rawItem->getType() == 3) && (player.type == 2)) {
            throw IllegalPurchaseException();
        }

        cout << "Selamat Anda berhasil membeli " << qty << " " << item.first << ". Uang Anda tersisa " << player.money << " gulden.\n\nPilih slot untuk menyimpan barang yang Anda beli!\n";
        PlayerView::printInventory(player);
        
        cout << "\nPetak slot: ";
        string location;
        cin >> location;
        if (location == "CANCEL") {
            throw UserCancelledPlayerViewException();
        }

        player.inventory.setItem(location, rawItem);
        cout << "\n" << item.first << " berhasil disimpan dalam penyimpanan!\n";
        
        if (item.second != -1) {
            this->shopInventory[item.first]--;
        }

    } catch (const exception &err){
        cout << err.what() << "\n";
    }
}

void Shop::printShopInventory() {
    cout << "Selamat datang di toko!!\nBerikut merupakan hal yang dapat Anda Beli\n";
    int i = 0;
    for(const auto& [key, value] : this->shopInventory) {
        if (value != 0) {
            shared_ptr<Item> tmp = itemFactory.createBaseItem(key);
            cout << i + 1 << ". " << tmp->getName() << " - " << tmp->getPrice() << " (" << value << ")\n";
            ++i;
        }
        else if(value == -1) {
            shared_ptr<Item> tmp = itemFactory.createBaseItem(key);
            cout << i + 1 << ". " << tmp->getName() << " - " << "price\n";
            ++i;
        }
    }
}
