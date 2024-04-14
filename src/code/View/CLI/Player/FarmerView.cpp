#include "View/CLI/Player/FarmerView.hpp"
#include "Exception/PlayerViewException.hpp"
#include "Model/Player/Farmer.hpp"
#include "View/CLI/CLI.hpp"

FarmerView::~FarmerView(){};
FarmerView *FarmerView::clone() { return new FarmerView(*this); }

void FarmerView::runSpecializedPlayerCommand(Player &player, string command) {
	Farmer &farmer = *(dynamic_cast<Farmer *>(&player));
	if (command == "TANAM") this->plant(farmer);
	else if (command == "PANEN") this->harvest(farmer);
	else if (command == "CETAK_LADANG") this->printFarm(farmer);
	else throw CommandNotFoundPlayerViewException();
}

void FarmerView::printFarm(Farmer &farmer) {
	function<string(FarmItem &)> fn = [](FarmItem &item) {
		string color;
		if (item.getAge() >= item.getDurationToHarvest()) color = GREEN;
		else color = RED;
		return color + item.getCode() + NORMAL;
	};

	CLI::printStorage("Ladang", farmer.getFarm(), fn);
}

void FarmerView::plant(Farmer &farmer) {
	while (true) {
		cout << "Pilih tanaman dari penyimpanan" << endl;
		this->printInventory(farmer);
		shared_ptr<FarmItem> farmItem;
		string inv_location = this->promptItemFromInventory(farmer, farmItem);
		this->printFarm(farmer);
		string plant_location = this->promptFieldFromFarm(farmer);
		try {
			farmer.plant(inv_location, plant_location);
			break;
		} catch (const std::exception &e) {
			std::cerr << e.what() << '\n';
		}
	}
}

void FarmerView::harvest(Farmer &farmer) {
	this->printFarm(farmer);
	vector<FarmItem *> field_item = farmer.getFarm().getAllItem();
	map<string, pair<int, string>> list_item;
	list_item.insert({"TEK", {0, "- TEK: Teak Tree"}});
	list_item.insert({"SDT", {0, "- SDT: Sandalwood Tree"}});
	list_item.insert({"ALT", {0, "- ALT: Aloe Tree"}});
	list_item.insert({"IRN", {0, "- IRN: Ironwood Tree"}});
	list_item.insert({"APL", {0, "- APL: Apple Tree"}});
	list_item.insert({"ORG", {0, "- ORG: Orange Tree"}});
	list_item.insert({"BNT", {0, "- BNT: Banana Tree"}});
	list_item.insert({"GAV", {0, "- GAV: Guava Tree"}});
	for (FarmItem *item : field_item) {
		if (item->getAge() >= item->getDurationToHarvest()) {
			list_item[item->getCode()].first += 1;
		}
	}
	cout << endl;
	bool can_harvest = false;
	for (const auto &item : list_item) {
		if (item.second.first != 0) {
			cout << item.second.second << endl;
			can_harvest = true;
		}
	}
	if (can_harvest) {
		cout << endl;
		int i = 1;
		cout << "Pilih tanaman siap panen yang kamu miliki: " << endl;
		vector<pair<int, pair<string, int>>> pick_list;
		for (auto item : list_item) {
			if (item.second.first != 0) {
				cout << i << ". " << item.first << " (" << item.second.first << " petak siap panen)" << endl;
				pick_list.push_back({i, {item.first, item.second.first}});
				i++;
			}
		}
		int no_tanaman = 0;
		while (true) {
			cout << "Nomor tanaman yang ingin dipanen: ";
			cin >> no_tanaman;
			if (cin.fail()) {
				cout << "Pastikan input telah sesuai!" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			if (no_tanaman > 0 && no_tanaman <= (int)pick_list.size()) {
				break;
			} else {
				cout << "Periksa kembali nomor tanaman yang dipilih" << endl;
			}
		}
		int amount = 0;
		while (true) {
			cout << "Berapa petak yang ingin dipanen: ";
			cin >> amount;
			if (cin.fail()) {
				cout << "Pastikan input telah sesuai!" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			if (amount <= pick_list.at(no_tanaman - 1).second.second && amount >= 0) {
				break;
			} else {
				cout << "Jumlah tanaman yang dapat dipanen lebih sedikit daripada yang ingin Anda panen!" << endl;
			}
		}
		for (int j = 0; j < amount; j++) {
			string plot_input;
			cout << "Petak ke-" << j + 1 << ": ";
			cin >> plot_input;
			if (cin.fail()) {
				cout << "Pastikan input telah sesuai!" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			while (pick_list.at(no_tanaman - 1).second.first != farmer.getFarm().getItem(plot_input)->getCode()) {
				cout << "Beda tanaman bang, pilih yang betul" << endl;
				cout << "Petak ke-" << j + 1 << ": ";
				cin >> plot_input;
			}
			farmer.harvestPlant(plot_input);
		}
	} else {
		cout << "Tanamannya masih belum bisa dipanen bos!" << endl;
	}
}
