#include "View/CLI/Player/FarmerView.hpp"
#include "Exception/PlayerViewException.hpp"

FarmerView::~FarmerView(){};
FarmerView *FarmerView::clone() { return new FarmerView(*this); }

void FarmerView::runSpecializedPlayerCommand(Player &player, string command) {
	Farmer &farmer = *(dynamic_cast<Farmer *>(&player));
	if (command == "TANAM") {
		this->plantHelper(farmer);
	} else throw CommandNotFoundPlayerViewException();
	if (command == "PANEN") {
		this->harvestHelper(farmer);
	} else throw;
	if (command == "CETAK_LADANG") {
		this->printFarm(farmer);
	} else throw;
}

void FarmerView::printFarm(Farmer &farmer) {
	auto &farmInventory = farmer.farm;
	auto size = farmInventory.getSize();
	for (int i = 0; i < size.first; i++)
	{
		cout << "| ";
		for (int j = 0; j < size.second; j++)
		{
			auto result = farmInventory.getItem(i,j);
			if (result.has_value())
			{
				cout << result->getCode();
			}
			else
			{
				cout << " ";
			}
			cout << " | ";
		}
		cout << endl;
	}
}

void FarmerView::plantHelper(Farmer &farmer) {
	cout << "Pilih tanaman dari penyimpanan" << endl;
	this->printInventory(farmer);
	shared_ptr<FarmItem> farmItem;
	string inv_location = this->promptItemFromInventory(farmer, farmItem);
	this->printFarm(farmer);
	string plant_location = this->promptFieldFromFarm(farmer);
	farmer.plant(inv_location, plant_location);
}

void FarmerView::harvestHelper(Farmer &farmer) {
	this->printFarm(farmer);
	//pair<int,int> field_size = farmer.farm.getSize();
	vector<FarmItem* > field_item = farmer.farm.getAllItem();
	//farmer.farm.getAllItem();
	vector<pair<string, int>> list_item;
	list_item.push_back({"TEK", 0});
	list_item.push_back({"SDT", 0});
	list_item.push_back({"ALT", 0});
	list_item.push_back({"IRN", 0});
	list_item.push_back({"APL", 0});
	list_item.push_back({"ORG", 0});
	list_item.push_back({"BNT", 0});
	list_item.push_back({"GAV", 0});
	for (FarmItem* item: field_item)
	{
		if (item->getAge() >= item->getDurationToHarvest())
		{
			if (item->getCode() == "TEK")
			{
				list_item[0].second += 1;
			}
			if (item->getCode() == "SDT")
			{
				list_item[1].second += 1;
			}
			if (item->getCode() == "ALT")
			{
				list_item[2].second += 1;
			}
			if (item->getCode() == "IRN")
			{
				list_item[3].second += 1;
			}
			if (item->getCode() == "APL")
			{
				list_item[4].second += 1;
			}
			if (item->getCode() == "ORG")
			{
				list_item[5].second += 1;
			}
			if (item->getCode() == "BNT")
			{
				list_item[6].second += 1;
			}
			if (item->getCode() == "GAV")
			{
				list_item[7].second += 1;
			}
		}
	}

	bool can_harvest = false;
	if (list_item[0].second != 0)
	{
		cout << "- TEK: Teak Tree";
		can_harvest = true;
	}
	if (list_item[1].second != 0)
	{
		cout << "- SDT: Sandalwood Tree";
		can_harvest = true;
	}
	if (list_item[2].second != 0)
	{
		cout << "- ALT: Aloe Tree";
		can_harvest = true;
	}
	if (list_item[3].second != 0)
	{
		cout << "- IRN: Ironwood Tree";
		can_harvest = true;
	}
	if (list_item[4].second != 0)
	{
		cout << "- APL: Apple Tree";
		can_harvest = true;
	}
	if (list_item[5].second != 0)
	{
		cout << "- ORG: Orange Tree";
		can_harvest = true;
	}
	if (list_item[6].second != 0)
	{
		cout << "- BNT: Banana Tree";
		can_harvest = true;
	}
	if (list_item[7].second != 0)
	{
		cout << "- GAV: Guava Tree";
		can_harvest = true;
	}
	if (can_harvest)
	{
		int i = 1;
		cout << "Pilih tanaman siap panen yang kamu miliki: " << endl;
		vector<pair<int, pair<string, int>>> pick_list;
		for (pair<string, int> item: list_item)
		{
			if (item.second != 0)
			{
				cout << i << ". " << item.first << "(" << item.second << "petak siap panen)" << endl;
				pick_list.push_back({i,item});
				i++;
			}	
		}
		int no_tanaman = 0;
		while (true)
		{
			cout << "Nomor tanaman yang ingin dipanen: " << endl;
			cin >> no_tanaman;
			if (no_tanaman > 0 && no_tanaman <= (int)pick_list.size())
			{
				break;
			}
			else
			{
				cout << "Periksa kembali nomor tanaman yang dipilih" << endl;
			}
		}
		int amount = 0;
		while (true)
		{
			cout << "Berapa petak yang ingin dipanen: " << endl;
			cin >> amount;
			if (amount <= pick_list.at(no_tanaman-1).second.second && amount >= 0)
			{
				break;
			}
			else
			{
				cout << "Jumlah tanaman yang dapat dipanen lebih sedikit daripada yang ingin Anda panen!" << endl;
			}
		}
		for (int j = 0; j < amount; j++)
		{
			string plot_input;
			cin >> plot_input;
			while (pick_list.at(no_tanaman-1).second.first != farmer.farm.getItem(plot_input)->getCode())
			{
				cout << "Beda tanaman bang, pilih yang betul" << endl;
				cin >> plot_input;
			}
			farmer.harvestPlant(plot_input);
		}
		
		
	}
	else
	{
		cout << "Tanamannya masih belum bisa dipanen bos!" << endl;
	}
}