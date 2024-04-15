#include "View/CLI/Player/BreederView.hpp"
#include "Exception/CLIException.hpp"
#include "View/CLI/CLI.hpp"
#include <algorithm>
#include <limits>

BreederView::~BreederView(){};
BreederView *BreederView::clone() { return new BreederView(*this); }
void BreederView::runSpecializedPlayerCommand(Player &player, string command) {
	Breeder &breeder = *(dynamic_cast<Breeder *>(&player));
	if (command == "TERNAK") this->breed(breeder);
	else if (command == "CETAK_PETERNAKAN") this->printBarn(breeder);
	else if (command == "KASIH_MAKAN") this->feed(breeder);
	else if (command == "PANEN") this->harvest(breeder);
	else throw CommandNotFoundCLIException();
}

void BreederView::printBarn(Breeder &breeder) {
	function<string(BarnItem &)> fn = [](BarnItem &item) {
		string color;
		if (item.getWeight() >= item.getWeightToHarvest()) color = GREEN;
		else color = RED;
		return color + item.getCode() + NORMAL;
	};

	CLI::printStorage("Peternakan", breeder.getBarn(), fn);
};

void BreederView::breed(Breeder &breeder) {
	string location;
	string locationAnimal;
	shared_ptr<BarnItem> barnItem;
	while (true) {
		PlayerView::printInventory(breeder);
		location = PlayerView::promptItemFromInventory(breeder, barnItem);
		BreederView::printBarn(breeder);
		locationAnimal = BreederView::promptFieldFromBarn(breeder, "Pilih petak yang ingin ditinggali: ", true);
		try {
			breeder.placeAnimal(location, locationAnimal);
			break;
		} catch (const std::exception &e) {
			std::cerr << e.what() << '\n';
		}
	}
};

void BreederView::feed(Breeder &breeder) {
	auto &barn = breeder.getBarn();
	if (barn.getFilledSpaceCount() == 0) {
		cout << "Peternakan Anda kosong" << endl;
		return;
	}

	function<string(optional<BarnItem> &)> animalValidator = [=](optional<BarnItem> &item) mutable {
		if (!item.has_value()) return "Petak ini kosong!";
		if (!breeder.hasProductToFeed(item->getBarnItemType())) return "Kamu tidak memiliki makanan untuk binatang ini!";
		return "";
	};
	BreederView::printBarn(breeder);
	string animalLocation = CLI::promptStorageLocation("Petak untuk diberi makan: ", breeder.getBarn(), animalValidator);
	auto &animal = breeder.getBarn().getItem(animalLocation).value();

	function<string(optional<shared_ptr<Item>> &)> foodValidator = [=](optional<shared_ptr<Item>> &item) mutable {
		if (!item.has_value()) return "Petak ini kosong!";
		if ((*item)->getType() != Product) return "Barang ini tidak bisa dimakan";

		BarnItemType type = animal.getBarnItemType();
		ProductItemType productType = dynamic_pointer_cast<ProductItem>(item.value())->getProductItemType();
		if (!Breeder::ableToFeed(type, productType)) {
			if (type == Herbivore) return "Ternak ini adalah vegetarian";
			else if (type == Carnivore) return "Ternak ini adalah kanibal";
			else if (productType == MaterialProduct) return "Ternak ini bukanlah bangunan";
		};

		return "";
	};
	PlayerView::printInventory(breeder);
	string foodLocation = CLI::promptStorageLocation("Petak untuk dimakan ternak: ", breeder.inventory, foodValidator);

	try {
		breeder.giveFood(foodLocation, animalLocation);
		cout << "Ternak " << animal.getName() << " telah diberi makan dan beratnya menjadi " << animal.getWeight() << endl;
	} catch (const exception &e) {
		cerr << e.what() << "\n";
	}
};

void BreederView::harvest(Breeder &breeder) {
	BreederView::printBarn(breeder);
	map<string, int> harvestables;
	for (auto item : breeder.getBarn().getAllItem()) {
		if (item->getWeight() > item->getWeightToHarvest()) {
			harvestables[item->getCode()] += 1;
		}
	}

	if (harvestables.size() == 0) {
		cout << "Tidak ada ternak yang bisa dipanen" << endl;
		return;
	}

	cout << "Pilih hewan siap panen yang kamu miliki" << endl;
	int i = 0;
	string nthCode[harvestables.size()];
	for (auto it : harvestables) {
		nthCode[i] = it.first;
		cout << '\t' << ++i << ". " << it.first << " (" << it.second << " petak siap panen)" << endl;
	}

	string selectedCode = nthCode[CLI::promptOption(1, i, "Nomor hewan yang ingin dipanen: ") - 1];
	int count = CLI::promptOption(1, harvestables[selectedCode], "Berapa petak yang ingin dipanen: ");

	cout << "Pilih petak yang ingin dipanen" << endl;
	function<string(optional<BarnItem> &)> fn = [=](optional<BarnItem> &item) {
		if (!item.has_value()) return "Tidak ada ternak disitu";
		else if (item->getCode() != selectedCode) return "Ternak tersebut bukan pilihan untuk dipanen";
		else if (item->getWeight() < item->getWeightToHarvest()) return "Ternak tersebut belum cukup tua untuk dipanen";
		return "";
	};

	for (int i = 0; i < count; ++i) {
		string harvestLocation = CLI::promptStorageLocation("Petak ke-" + to_string(i + 1) + " dipanen: ", breeder.getBarn(), fn);
		breeder.harvestAnimal(harvestLocation);
	}
};
