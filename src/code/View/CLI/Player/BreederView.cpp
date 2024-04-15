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

	CLI::printStorage("Peternakan", breeder.getField(), fn);
};

void BreederView::breed(Breeder &breeder) {
	string inventoryLocation;
	string fieldLocation;
	shared_ptr<BarnItem> barnItem;
	while (true) {
		PlayerView::printInventory(breeder);
		inventoryLocation = PlayerView::promptItemFromInventory(breeder, barnItem);
		BreederView::printBarn(breeder);
		fieldLocation = BreederView::promptFieldFromBarn(breeder, "Pilih petak yang ingin ditinggali: ", true);
		try {
			breeder.place(inventoryLocation, fieldLocation);
			break;
		} catch (const std::exception &e) {
			std::cerr << e.what() << '\n';
		}
	}
};

void BreederView::feed(Breeder &breeder) {
	auto &barn = breeder.getField();
	if (barn.getFilledSpaceCount() == 0) {
		cout << "Peternakan Anda kosong" << endl;
		return;
	}

	function<void(optional<BarnItem> &)> animalValidator = [&](optional<BarnItem> &item) mutable {
		if (!item.has_value()) throw PromptException("Petak ini kosong!");
		if (!breeder.hasProductToFeed(item->getBarnItemType())) throw PromptException("Kamu tidak memiliki makanan untuk binatang ini!");
	};
	BreederView::printBarn(breeder);
	string animalLocation = CLI::promptStorageLocation("Petak untuk diberi makan: ", breeder.getField(), animalValidator);
	auto &animal = breeder.getField().getItem(animalLocation).value();

	function<void(optional<shared_ptr<Item>> &)> foodValidator = [=](optional<shared_ptr<Item>> &item) mutable {
		if (!item.has_value()) throw PromptException("Petak ini kosong!");
		if ((*item)->getType() != Product) throw PromptException("Barang ini tidak bisa dimakan");

		BarnItemType type = animal.getBarnItemType();
		ProductItemType productType = dynamic_pointer_cast<ProductItem>(item.value())->getProductItemType();
		if (!Breeder::ableToFeed(type, productType)) {
			if (type == Herbivore) throw PromptException("Ternak ini adalah vegetarian");
			else if (type == Carnivore) throw PromptException("Ternak ini adalah kanibal");
			else if (productType == MaterialProduct) throw PromptException("Ternak ini bukanlah bangunan");
		};
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
	for (auto item : breeder.getField().getAllItem()) {
		if (item->getWeight() >= item->getWeightToHarvest()) {
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
	function<void(optional<BarnItem> &)> fn = [=](optional<BarnItem> &item) {
		if (!item.has_value()) throw PromptException("Tidak ada ternak disitu");
		else if (item->getCode() != selectedCode) throw PromptException("Ternak tersebut bukan pilihan untuk dipanen");
		else if (item->getWeight() < item->getWeightToHarvest()) throw PromptException("Ternak tersebut belum cukup tua untuk dipanen");
	};

	for (int i = 0; i < count; ++i) {
		string harvestLocation = CLI::promptStorageLocation("Petak ke-" + to_string(i + 1) + " dipanen: ", breeder.getField(), fn);
		breeder.harvestAnimal(harvestLocation);
	}
};
