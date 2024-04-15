#include "View/CLI/ShopView.hpp"
#include "Container/Storage.hpp"
#include "Exception/CLIException.hpp"
#include "Exception/PromptException.hpp"
#include "Exception/StorageException.hpp"
#include "Model/Item.hpp"
#include "View/CLI/CLI.hpp"
#include <climits>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void ShopView::sellItem(Player &player) {
	PlayerView::printInventory(player);
	auto &shop = player.getContext().getShopController();

	while (true) {
		function<void(string, optional<shared_ptr<Item>> &)> fn = [&](string, optional<shared_ptr<Item>> &opt) mutable {
			if (!opt.has_value())
				throw PromptException("Tidak bisa menjual petak kosong!");

			auto &item = opt.value();
			if (!shop.getAccepted(player.getType(), item->getType()))
				throw PromptException("Barang tersebut tidak bisa dijual!");
		};
		string location = CLI::promptStorageLocation("Petak untuk dijual (CANCEL untuk berhenti): ", player.inventory, fn);
		int price = player.inventory.getItem(location).value()->getPrice();
		player.setMoney(player.getMoney() + price);
		player.inventory.clearItem(location);

		cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << price << " gulden!" << endl;
		PlayerView::printInventory(player);
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
	for (auto &[count, name] : sorted) {
		if (count == 0) continue;
		cout << ++i << ". ";
		cout << name << " - ";
		auto price = itemFactory.getItemByName(name)->getPrice();
		cout << price;
		if (count != -1)
			cout << " (" << count << ")";
		cout << endl;
		nthList.push_back(name);
	}

	cout << "Uang anda: " << player.getMoney() << endl;
	cout << "Slot penyimpanan tersedia: " << player.inventory.getEmptySpaceCount() << endl;

	int listSize = nthList.size();
	string selectedName = nthList[CLI::promptOption(1, listSize, "Barang yang ingin dibeli: ") - 1];

	function<pair<int, int>(string)> validator = [&](string input) -> pair<int, int> {
		int quantity = atoi(input.c_str());
		if (quantity <= 0) throw PromptException("Kuantitas tidak valid!");
		if (catalogue[selectedName] != -1 && quantity > catalogue[selectedName]) throw PromptException("Barang pada toko tidak cukup!");
		if (quantity > inventory.getEmptySpaceCount()) throw PromptException("Penyimpanan pemain tidak cukup!");

		int totalPrice = itemFactory.getItemByName(selectedName)->getPrice() * quantity;
		if (totalPrice > player.getMoney()) throw PromptException("Uang pemain tidak cukup!");

		return {quantity, totalPrice};
	};
	auto [quantity, totalPrice] = CLI::prompt("Kuantitas: ", validator);

	set<string> slots;
	PlayerView::printInventory(player);

	cout << "Pilih slot untuk menyimpan barang yang Anda beli!" << endl;
	for (int i = 0; i < quantity; ++i) {
		function<void(string, optional<shared_ptr<Item>> &)> fn = [&](string input, optional<shared_ptr<Item>> &item) {
			if (item.has_value())
				throw PromptException("Tidak bisa memilih petak yang sudah digunakan!");

			if (slots.contains(input))
				throw PromptException("Petak tersebut sudah dipilih!");
		};
		slots.insert(CLI::promptStorageLocation("Petak ke-" + to_string(i + 1) + ": ", player.inventory, fn));
	}

	player.setMoney(player.getMoney() - totalPrice);
	shop.removeItem(itemFactory.getItemByName(selectedName));
	cout << "Selamat Anda berhasil membeli " + to_string(quantity) + " " + selectedName + ". Uang Anda tersisa " + to_string(player.getMoney()) + " gulden." << endl;
	for (auto &slot : slots) {
		shared_ptr<Item> item = itemFactory.createBaseItemByName(selectedName);
		inventory.setItem(slot, item);
	}
};
