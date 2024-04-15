#include "View/CLI/Player/MayorView.hpp"
#include "Exception/CLIException.hpp"
#include "Model/Item/BuildingItem.hpp"
#include "Model/Player.hpp"
#include "Model/Player/Mayor.hpp"

MayorView::~MayorView(){};
MayorView *MayorView::clone() { return new MayorView(*this); }

void MayorView::runSpecializedPlayerCommand(Player &player, string command) {
	Mayor &mayor = *(dynamic_cast<Mayor *>(&player));
	if (command == "PUNGUT_PAJAK") this->collectTax(mayor);
	else if (command == "BANGUN") this->build(mayor);
	else if (command == "TAMBAH_PEMAIN") this->addPlayer(mayor);
	else throw CommandNotFoundCLIException();
}

void MayorView::collectTax(Mayor &mayor) {
	vector<pair<shared_ptr<Player>, int>> pajakTerpungut = mayor.collectTax();
	int i = 0;
	int sum = 0;
	cout << "Cring cring cring..." << endl;
	cout << "Pajak sudah dipungut!" << endl;
	cout << "Berikut adalah detil dari pemungutan pajak:" << endl;
	for (const auto &pair : pajakTerpungut) {
		cout << ++i << ". " << pair.first->getUsername() << " - " << Player::playerTypeToString(pair.first->getType()) << ": " << pair.second << " gulden" << endl;
		sum += pair.second;
	}
	cout << "Negara mendapatkan pemasukan sebesar " << sum << " gulden." << endl;
	cout << "Gunakan dengan baik dan jangan dikorupsi ya!" << endl;
};

void MayorView::build(Mayor &mayor) {
	auto &items = mayor.getContext().getItemFactory().getRepository();

	map<string, shared_ptr<BuildingItem>> recipes;
	for (auto &[_, item] : items) {
		shared_ptr<BuildingItem> building = dynamic_pointer_cast<BuildingItem>(item);
		if (building == nullptr) continue;
		recipes[building->getName()] = building;
	}

	cout << "Resep bangunan yang ada adalah sebagai berikut:" << endl;
	int i = 0;
	for (auto &[name, building] : recipes) {
		cout << ++i << ". " << name << " (" << building->getPrice() << " GULDEN";
		for (auto &[ingredient, count] : building->getIngredients()) {
			cout << ", " << ingredient << " " << count;
		}
		cout << ")" << endl;
	}

	while (true) {
		string name;
		cout << "Bangunan yang ingin dibangun: ";
		cin >> name;
		if (name == "CANCEL") throw UserCancelledCLIException();

		if (!recipes.contains(name)) {
			cout << "Kamu tidak punya resep bangunan tersebut!";
			continue;
		}

		auto &building = recipes[name];
		int money = mayor.getMoney() - building->getPrice();
		auto [locations, remaining] = mayor.checkInventory(building->getIngredients());

		if (remaining.size() != 0 || money < 0) {
			cout << "Kamu tidak punya sumber daya yang cukup! Masih memerlukan ";

			vector<string> needs;
			if (money < 0) needs.push_back(to_string(money * -1) + " GULDEN");
			for (auto &[ingredient, count] : remaining) needs.push_back(to_string(count) + " " + ingredient);

			int size = needs.size();
			for (int i = 0; i < size; ++i) {
				cout << needs[i];
				if (i != size - 1) cout << ", ";
			}
			cout << endl;
			continue;
		}

		mayor.buildBuilding(name, locations);
		cout << name << " berhasil dibangun dan telah menjadi hak milik walikota!" << endl;

		break;
	}
};

void MayorView::addPlayer(Mayor &mayor) {
	mayor.isEnoughMoney();
	string username;
	string type;
	cout << "Masukkan jenis pemain: ";
	cin >> type;
	cout << "Masukkan nama pemain: ";
	cin >> username;
	mayor.addPlayer(username, type);
	cout << "Pemain baru ditambahkan!" << endl;
	cout << "Selamat datang " << username << " di kota ini!" << endl;
};
