#include "View/CLI/ShopView.hpp"
#include "Container/Storage.hpp"
#include "Exception/PlayerViewException.hpp"
#include "Exception/ShopException.hpp"
#include "Exception/StorageException.hpp"
#include "Model/Item.hpp"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void ShopView::sellItem(Player &player) {
	PlayerView::printInventory(player);
	auto &shop = player.getContext().getShopController();

	while (true) {
		cout << "Petak untuk dijual (CANCEL untuk berhenti): ";
		string location;
		cin >> location;
		cin.ignore(INT_MAX, '\n');
		if (location == "CANCEL") throw UserCancelledPlayerViewException();

		try {
			auto &opt = player.inventory.getItem(location);
			if (!opt.has_value()) {
				cout << "Slot penyimpanan tersebut kosong" << endl;
				continue;
			}

			auto &item = opt.value();
			if (!shop.getAccepted(player.getType(), item->getType())) {
				cout << "Barang tidak bisa dijual" << endl;
				continue;
			}

			int price = item->getPrice();
			player.setMoney(player.getMoney() + price);
			player.inventory.clearItem(location);

			cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << price << " gulden!" << endl;
			PlayerView::printInventory(player);
		} catch (const std::exception &err) {
			cout << err.what() << endl;
		}
	}
};

void ShopView::buyItem(Player &player) {
	auto &itemFactory = player.getContext().getItemFactory();
	auto &shop = player.getContext().getShopController();
	auto &inventory = player.inventory;
	auto catalogue = shop.getCatalogue(player.getType());

	vector<pair<int, string>> sorted;
	for (auto &it : catalogue) {
		sorted.push_back({it.second, it.first});
	}
	sort(sorted.begin(), sorted.end(), greater());

	vector<string> nthList;

	int i = 0;
	for (auto &it : sorted) {
		if (it.first == 0) continue;
		cout << ++i << ". ";
		cout << it.second << " - ";
		auto code = itemFactory.getCodeByName(it.second);
		auto price = itemFactory.getItemByCode(code)->getPrice();
		cout << price;
		if (it.first != -1)
			cout << " (" << it.first << ")";
		cout << endl;
		nthList.push_back(it.second);
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

		int nth = atoi(input.c_str());
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

		quantity = atoi(input.c_str());
		if (quantity <= 0) {
			cout << "Kuantitas tidak valid!" << endl;
			continue;
		}

		if (catalogue[selectedName] != -1 && quantity > catalogue[selectedName]) {
			cout << "Barang pada toko tidak cukup!" << endl;
			continue;
		}

		if (quantity > inventory.getEmptySpaceCount()) {
			cout << "Penyimpanan pemain tidak cukup!" << endl;
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
	PlayerView::printInventory(player);
};
