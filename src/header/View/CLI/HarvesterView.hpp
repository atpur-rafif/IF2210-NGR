#ifndef VIEW_CLI_HARVESTERVIEW_HPP
#define VIEW_CLI_HARVESTERVIEW_HPP

#include "Color/pcolor.hpp"
#include "View/CLI/CLI.hpp"
#include "View/CLI/PlayerView.hpp"
#include <functional>

class HarvesterView : public PlayerView {
public:
	template <class T>
	static void printField(Harvester<T> &harvester) {
		function<string(T &)> fn = [](T &item) {
			string color;
			if (item.harvestable()) color = GREEN;
			else color = RED;
			return color + item.getCode() + NORMAL;
		};

		CLI::printStorage(T::fieldName, harvester.getField(), fn);
	}

	template <class T>
	static void place(Harvester<T> &harvester) {
		string inventoryLocation;
		string fieldLocation;
		while (true) {
			PlayerView::printInventory(harvester);
			function<void(string, optional<shared_ptr<Item>> &)> inventoryValidator = [](string, optional<shared_ptr<Item>> &item) {
				T testItem; // Temporary to make sure the same type
				if (!item.has_value())
					throw PromptException("Penyimpanan kosong pada lokasi tersebut");
				if (item.value()->getType() != testItem.getType())
					throw PromptException("Tipe barang tidak valid");
			};
			inventoryLocation = CLI::promptStorageLocation("Pilih barang sebagai " + T::pronoun + ": ", harvester.inventory, inventoryValidator);

			HarvesterView::printField(harvester);
			function<void(string, optional<T> &)> fieldValidator = [](string, optional<T> &harvestable) {
				if (harvestable.has_value()) throw PromptException("Tidak bisa menggunakan petak yang sudah ditempati");
			};
			fieldLocation = CLI::promptStorageLocation("Pilih petak yang ingin diletakan " + T::pronoun + ": ", harvester.getField(), fieldValidator);

			try {
				harvester.place(inventoryLocation, fieldLocation);
				break;
			} catch (const std::exception &e) {
				std::cerr << e.what() << '\n';
			}
		}
	};

	template <class T>
	static void harvest(Harvester<T> &harvester) {
		HarvesterView::printField(harvester);
		map<string, int> harvestables;
		for (auto item : harvester.getField().getAllItem()) {
			if (item->harvestable()) {
				harvestables[item->getCode()] += 1;
			}
		}

		if (harvestables.size() == 0) {
			cout << "Tidak ada " << T::pronoun << " yang bisa dipanen" << endl;
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
		function<void(string, optional<T> &)> fn = [=](string, optional<T> &item) {
			if (!item.has_value()) throw PromptException("Tidak ada ternak disitu");
			else if (item->getCode() != selectedCode) throw PromptException("Ternak tersebut bukan pilihan untuk dipanen");
			else if (!item->harvestable()) throw PromptException("Ternak tersebut belum cukup tua untuk dipanen");
		};

		for (int i = 0; i < count; ++i) {
			string harvestLocation = CLI::promptStorageLocation("Petak ke-" + to_string(i + 1) + " dipanen: ", harvester.getField(), fn);
			harvester.harvest(harvestLocation);
		}
	};
};

#endif
