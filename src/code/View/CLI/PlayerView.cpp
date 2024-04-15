#include "View/CLI/PlayerView.hpp"
#include "Exception/CLIException.hpp"
#include "Exception/GameException.hpp"
#include "Model/Item//ProductItem.hpp"
#include "View/CLI/CLI.hpp"
#include "View/CLI/ShopView.hpp"
#include "View/Config/Config.hpp"
#include <functional>
#include <iomanip>
#include <iostream>
using namespace std;

PlayerView::~PlayerView(){};

void PlayerView::start(Player &player) {
	while (true) {
		cout << player.getUsername() << "> ";
		string command;
		cin >> command;
		if (command == "NEXT") {
			auto list_player = player.getContext().getPlayerController().getPlayers();
			int size = list_player.size();
			for (int i = 0; i < size; ++i) {
				auto farmer_player = list_player.at(i).get();
				if (farmer_player->getType() == FarmerType) {
					Farmer &farmer = *(dynamic_cast<Farmer *>(farmer_player));
					farmer.plantsGrow();
				}
			}
			return;
		}

		try {
			try {
				this->runPlayerCommand(player, command);
				continue;
			} catch (const CommandNotFoundCLIException &_) {
			} catch (...) {
				throw;
			}
			this->runSpecializedPlayerCommand(player, command);
			continue;
		} catch (const CLIException &err) {
			cout << err.what() << endl;
		}
	}
}

void PlayerView::runPlayerCommand(Player &player, string command) {
	if (command == "BELI") ShopView::buyItem(player);
	else if (command == "JUAL") ShopView::sellItem(player);
	else if (command == "CETAK_PENYIMPANAN") this->printInventory(player);
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

		player.setWeight(player.getWeight() + product->getAddedWeight());
		player.inventory.clearItem(location);
	} else if (command == "STATUS") {
		cout << "Money: " << player.getMoney() << endl;
		cout << "Weight: " << player.getWeight() << endl;
	} else if (command == "SIMPAN") {
		cout << "Location to save: ";
		string location;
		cin >> location;
		Config::writeState(location, player.getContext());
	} else throw CommandNotFoundCLIException();
}

void PlayerView::printInventory(Player &player) {
	function<string(shared_ptr<Item> &)> fn = [](shared_ptr<Item> &item) {
		return item->getCode();
	};

	CLI::printStorage("Penyimpanan", player.inventory, fn);
};
