#include "View/CLI/PlayerView.hpp"
#include "Exception/PlayerViewException.hpp"
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
		} catch (const PlayerViewException &err) {
			cout << err.what() << endl;
		}
	}
}

void PlayerView::runPlayerCommand(Player &player, string command) {
	if (command == "CETAK_PENYIMPANAN") this->printInventory(player);
	else throw CommandNotFoundPlayerViewException();
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
