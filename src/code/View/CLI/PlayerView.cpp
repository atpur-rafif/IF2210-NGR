#include "View/CLI/PlayerView.hpp"
#include "Exception/GameException.hpp"
#include "Exception/PlayerViewException.hpp"
#include "Model/Item//ProductItem.hpp"
#include "View/Config/Config.hpp"
#include <iostream>
using namespace std;

PlayerView::~PlayerView(){};

void PlayerView::start(Player &player) {
	while (true) {
		cout << player.username << "> ";
		string command;
		cin >> command;
		if (command == "NEXT") return;

		try {
			try {
				this->runPlayerCommand(player, command);
				continue;
			} catch (const CommandNotFoundPlayerViewException &_) {
			} catch (...) {
				throw;
			}
			this->runSpecializedPlayerCommand(player, command);
			continue;
		} catch (const GameException &err) {
			cout << err.what() << endl;
		}
	}
}

void PlayerView::runPlayerCommand(Player &player, string command) {
	if (command == "CETAK_PENYIMPANAN") this->printInventory(player);
	else if (command == "MAKAN") {
		this->printInventory(player);

		string location;
		shared_ptr<ProductItem> product;
		while (true) {
			location = this->promptItemFromInventory(player, product);
			ProductItemType type = product->getProductItemType();
			if (type == AnimalProduct || type == FruitProduct) break;
			cout << "Player can't eat this item" << endl;
		}

		player.weight += product->getAddedWeight();
		player.inventory.clearItem(location);
	} else if (command == "STATUS") {
		cout << "Money: " << player.money << endl;
		cout << "Weight: " << player.weight << endl;
	} else if (command == "SIMPAN") {
		cout << "Location to save: ";
		string location;
		cin >> location;
		Config::writeState(location, player.getContext());
	} else throw CommandNotFoundPlayerViewException();
}

void PlayerView::printInventory(Player &player) {
	auto &inventory = player.inventory;
	auto size = inventory.getSize();
	for (int y = 0; y < size.first; ++y) {
		cout << "| ";
		for (int x = 0; x < size.second; ++x) {
			auto result = inventory.getItem(x, y);
			if (result.has_value()) cout << result.value()->getCode();
			else cout << "   ";
			cout << " | ";
		}
		cout << endl;
	}
};
