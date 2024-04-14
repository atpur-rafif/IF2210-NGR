#include "View/CLI/Shop.hpp"
#include "Container/Storage.hpp"
#include "Exception/PlayerViewException.hpp"
#include "Exception/ShopException.hpp"
#include "Exception/StorageException.hpp"
#include "Model/Item.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void ShopView::sellItem(Player &player) {
	(void)player;
};

void ShopView::buyItem(Player &player) {
	auto &itemFactory = player.getContext().getItemFactory();
	auto &shop = player.getContext().getShopController();
	auto &inventory = player.inventory;
	auto catalogue = shop.getCatalogue(player.getType());

	vector<string> nthList;

	int i = 0;
	for (auto &it : catalogue) {
		if (it.second == 0) continue;
		cout << ++i << ". ";
		cout << it.first << " - ";
		auto code = itemFactory.getCodeByName(it.first);
		auto price = itemFactory.getItemByCode(code)->getPrice();
		cout << price;
		if (it.second != -1)
			cout << " (" << it.second << ")";
		cout << endl;
		nthList.push_back(it.first);
	}

	cout << "Uang anda: " << player.getMoney() << endl;
	cout << "Slot penyimpanan tersedia: " << player.inventory.getEmptySpaceCount() << endl;

	string selectedName;
	int listSize = nthList.size();
	while (true) {
		string input;
		cout << "Barang ingin dibeli: ";
		cin >> input;
		cin.ignore(INT_MAX, '\n');

		if (input == "CANCEL") throw UserCancelledPlayerViewException();

		int nth = stoi(input);
		if (1 <= nth && nth <= listSize) {
			selectedName = nthList[nth - 1];
			break;
		}
		cout << "Pilihan tidak valid" << endl;
	}

	int quantity;
	int totalPrice;
	string code = itemFactory.getCodeByName(selectedName);

	while (true) {
		string input;
		cout << "Kuantitas: ";
		cin >> input;
		cin.ignore(INT_MAX, '\n');

		if (input == "CANCEL") throw UserCancelledPlayerViewException();

		quantity = stoi(input);
		if (quantity <= 0) {
			cout << "Kuantitas tidak valid!" << endl;
			continue;
		}

		if (quantity > catalogue[selectedName]) {
			cout << "Barang pada toko tidak cukup!" << endl;
			continue;
		}

		totalPrice = itemFactory.getItemByCode(code)->getPrice() * quantity;
		if (totalPrice > player.getMoney()) {
			cout << "Uang tidak cukup!" << endl;
			continue;
		}

		break;
	}

	vector<pair<int, int>> slots;
	PlayerView::printInventory(player);

	cout << "Pilih slot untuk menyimpan barang yang Anda beli!" << endl;
	int size = slots.size();
	while (size < quantity) {
		try {
			cout << "Slot ke-" << size + 1 << ": ";
			string location;
			cin >> location;
			cin.ignore(INT_MAX, '\n');

			if (location == "CANCEL")
				throw UserCancelledPlayerViewException();

			auto slot = inventory.decodeCoordinate(location);
			if (inventory.getItem(slot.first, slot.second).has_value()) {
				cout << "Slot tersebut sudah terisi" << endl;
				continue;
			}

			slots.push_back(slot);
		} catch (const std::exception &err) {
			cout << err.what() << endl;
		}

		size = slots.size();
	}

	player.setMoney(player.getMoney() - totalPrice);
	cout << "Selamat Anda berhasil membeli " + to_string(quantity) + " " + selectedName + ". Uang Anda tersisa " + to_string(player.getMoney()) + " gulden." << endl;
	for (auto &slot : slots) {
		shared_ptr<Item> item = itemFactory.createBaseItem(code);
		inventory.setItem(slot.first, slot.second, item);
	}
};
