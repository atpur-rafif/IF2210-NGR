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
			player.getContext().getPlayerController().checkWinner();
			continue;
		} catch (const CLIException &err) {
			cout << err.what() << endl;
		}
	}
}

void PlayerView::eat(Player &player) {
	auto items = player.inventory.getAllItem();
	bool found = false;
	for (auto item : items) {
		if ((*item)->getType() != Product) continue;

		shared_ptr<ProductItem> product = dynamic_pointer_cast<ProductItem>(*item);
		if (product->getProductItemType() != MaterialProduct) {
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "Kamu tidak memiliki barang yang bisa dimakan!" << endl;
		return;
	}

	PlayerView::printInventory(player);
	function<void(string, optional<shared_ptr<Item>> &)> fn = [](string, optional<shared_ptr<Item>> &opt) {
		if (!opt.has_value())
			throw PromptException("Tidak bisa memakan petak kosong");

		shared_ptr<ProductItem> product = dynamic_pointer_cast<ProductItem>(opt.value());
		if (product == nullptr)
			throw PromptException("Barang yang dipilih tidak bisa dimakan");

		if (product->getProductItemType() == MaterialProduct)
			throw PromptException("Tidak bisa memakan material");
	};
	string location = CLI::promptStorageLocation("Petak untuk dimakan: ", player.inventory, fn);
	player.eat(location);
}

void PlayerView::save(Player &player) {
	cout << "Location to save: ";
	string location;
	cin >> location;
	Config::writeState(location, player.getContext());
}

void PlayerView::runPlayerCommand(Player &player, string command) {
	if (command == "BELI") ShopView::buyItem(player);
	else if (command == "JUAL") ShopView::sellItem(player);
	else if (command == "CETAK_PENYIMPANAN") this->printInventory(player);
	else if (command == "MAKAN") this->eat(player);
	else if (command == "STATUS") {
		cout << "Money: " << player.getMoney() << endl;
		cout << "Weight: " << player.getWeight() << endl;
	} else if (command == "SIMPAN") this->save(player);
	else throw CommandNotFoundCLIException();
}

void PlayerView::printInventory(Player &player) {
	function<string(shared_ptr<Item> &)> fn = [](shared_ptr<Item> &item) {
		return item->getCode();
	};

	CLI::printStorage("Penyimpanan", player.inventory, fn);
};
