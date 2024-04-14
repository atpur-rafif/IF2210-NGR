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
	FarmerView::printFarm(farmer);
	map<string, int> harvestables;
	for (auto item : farmer.getFarm().getAllItem()) {
		if (item->getAge() > item->getDurationToHarvest()) {
			harvestables[item->getCode()] += 1;
		}
	}

	if (harvestables.size() == 0) {
		cout << "Tidak ada tanaman yang bisa dipanen" << endl;
		return;
	}

	cout << "Pilih tanaman siap panen yang kamu miliki" << endl;
	int i = 0;
	string nthCode[harvestables.size()];
	for (auto it : harvestables) {
		nthCode[i] = it.first;
		cout << '\t' << ++i << ". " << it.first << " (" << it.second << " petak siap panen)" << endl;
	}

	string selectedCode = nthCode[CLI::promptOption(1, i, "Nomor tanaman yang ingin dipanen: ") - 1];
	int count = CLI::promptOption(1, harvestables[selectedCode], "Berapa petak yang ingin dipanen: ");

	cout << "Pilih petak yang ingin dipanen" << endl;
	function<string(optional<FarmItem> &)> fn = [=](optional<FarmItem> &item) {
		if (!item.has_value()) return "Tidak ada tanaman disitu";
		else if (item->getCode() != selectedCode) return "Tanaman tersebut bukan pilihan untuk dipanen";
		else if (item->getAge() < item->getDurationToHarvest()) return "Ternak tersebut belum cukup tua untuk dipanen";
		return "";
	};

	for (int i = 0; i < count; ++i) {
		string harvestLocation = CLI::promptStorageLocation("Petak ke-" + to_string(i + 1) + " dipanen: ", farmer.getFarm(), fn);
		farmer.harvestPlant(harvestLocation);
	}
}
