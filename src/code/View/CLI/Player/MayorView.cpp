#include "View/CLI/Player/MayorView.hpp"
#include "Exception/CLIException.hpp"
#include "Exception/PromptException.hpp"
#include "Model/Item/BuildingItem.hpp"
#include "Model/Player.hpp"
#include "Model/Player/Mayor.hpp"
#include "View/CLI/CLI.hpp"

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

	function<pair<string, vector<string>>(string)> nameValidator = [&](string name) -> pair<string, vector<string>> {
		if (!recipes.contains(name))
			throw PromptException("Kamu tidak punya resep bangunan tersebut!");

		auto &building = recipes[name];
		auto [locations, remaining] = mayor.checkInventory(building->getIngredients());

		if (remaining.size() != 0) {
			string err = "";
			err += "Kamu tidak punya sumber daya yang cukup! Masih memerlukan ";

			vector<string> needs;
			for (auto &[ingredient, count] : remaining) needs.push_back(to_string(count) + " " + ingredient);

			int size = needs.size();
			for (int i = 0; i < size; ++i) {
				err += needs[i];
				if (i != size - 1) err += ", ";
			}

			throw PromptException(err);
		}

		return {name, locations};
	};
	auto [name, locations] = CLI::prompt("Bangunan yang ingin dibangun: ", nameValidator);

	mayor.buildBuilding(name, locations);
	cout << name << " berhasil dibangun dan telah menjadi hak milik walikota!" << endl;
};

void MayorView::addPlayer(Mayor &mayor) {
	auto &playerController = mayor.getContext().getPlayerController();

	if (mayor.getMoney() < Mayor::newPlayerMoney) {
		cout << "Kamu tidak memiliki cukup uang!" << endl;
		return;
	}

	function<PlayerType(string)> typeValidator = [&](string type) {
		auto opt = Player::stringToPlayerType(type);
		if (!opt.has_value())
			throw PromptException("Tipe pemain tidak valid!");

		auto value = opt.value();
		if (value == MayorType && playerController.hasMayor())
			throw PromptException("Hanya boleh ada satu Walikota dalam permainan");

		return value;
	};
	PlayerType type = CLI::prompt("Tipe pemain: ", typeValidator);

	function<string(string)> usernameValidator = [&](string input) {
		if (!playerController.validateNewUsername(input))
			throw PromptException("Nama tersebut telah digunakan");

		return input;
	};
	string username = CLI::prompt("Masukkan nama pemain: ", usernameValidator);

	mayor.addPlayer(username, type);
	cout << "Selamat datang " << username << " di kota ini!" << endl;
};
