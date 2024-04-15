#include "View/CLI/Player/BreederView.hpp"
#include "Exception/CLIException.hpp"
#include "View/CLI/CLI.hpp"
#include "View/CLI/HarvesterView.hpp"
#include <algorithm>
#include <limits>

BreederView::~BreederView(){};
BreederView *BreederView::clone() { return new BreederView(*this); }
void BreederView::runSpecializedPlayerCommand(Player &player, string command) {
	Breeder &breeder = *(dynamic_cast<Breeder *>(&player));
	if (command == "TERNAK") this->place(breeder);
	else if (command == "CETAK_PETERNAKAN") this->printField(breeder);
	else if (command == "KASIH_MAKAN") this->place(breeder);
	else if (command == "PANEN") this->harvest(breeder);
	else throw CommandNotFoundCLIException();
}

void BreederView::feed(Breeder &breeder) {
	auto &barn = breeder.getField();
	if (barn.getFilledSpaceCount() == 0) {
		cout << "Peternakan Anda kosong" << endl;
		return;
	}

	function<void(string, optional<BarnItem> &)> animalValidator = [&](string, optional<BarnItem> &item) mutable {
		if (!item.has_value()) throw PromptException("Petak ini kosong!");
		if (!breeder.hasProductToFeed(item->getBarnItemType())) throw PromptException("Kamu tidak memiliki makanan untuk binatang ini!");
	};
	BreederView::printField(breeder);
	string animalLocation = CLI::promptStorageLocation("Petak untuk diberi makan: ", breeder.getField(), animalValidator);
	auto &animal = breeder.getField().getItem(animalLocation).value();

	function<void(string, optional<shared_ptr<Item>> &)> foodValidator = [=](string, optional<shared_ptr<Item>> &item) mutable {
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
