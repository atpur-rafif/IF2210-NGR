#include "View/CLI/Player/BreederView.hpp"
#include "Exception/PlayerViewException.hpp"
#include <algorithm>


BreederView::~BreederView(){};
BreederView *BreederView::clone() { return new BreederView(*this); }
void BreederView::runSpecializedPlayerCommand(Player &player, string command) {
	Breeder &breeder = *(dynamic_cast<Breeder *>(&player));
	if (command == "TERNAK") {
		
		string location; 
		string locationAnimal;
		shared_ptr<BarnItem> barnItem; 
		while(true){
			this->printInventory(player); 
			location = this->promptItemFromInventory(player, barnItem); 
			this->printBarn(breeder);
			locationAnimal = this->promptFieldFromBarn(breeder, "Pilih petak yang ingin ditinggali: ", true);
			try
			{
				breeder.placeAnimal(location, locationAnimal);
				break;
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			
		}

	}
	else if (command == "BARN"){
		printBarn(breeder);
	}
	else if (command == "KASIH_MAKAN"){
		while(true){
			string loc; 
			string locFood; 
			shared_ptr<ProductItem> foodItem; 	
			//Ini perintah kasih makannya
			this->printBarn(breeder);
			loc = this->promptFieldFromBarn(breeder, "Pilih petak yang ingin diberi makan: ", false); 
			breeder.giveFoodChecker(loc);
			this->printInventory(player); 
			locFood = this->promptItemFromInventory(player, foodItem);
			try{
				breeder.giveFood(locFood, loc);
				break;
			}
			catch(const exception& e){
				cerr << e.what() << "\n";
			}
		}
	}
	else if(command == "PANEN"){
		string choose; 
		string total; 
		vector<pair<int, string>> listNumber;

		cout << "========================PETERNAKAN==============================\n";
		detail(breeder); 
	}
	else {
		throw CommandNotFoundPlayerViewException(); 
	}

}

void BreederView::printBarn(Breeder& breeder){
	auto &barnInventory = breeder.barn; 
	auto size = barnInventory.getSize();
	for(int y = 0; y < size.first; y++){
		cout << "| "; 
		for(int x = 0; x < size.second; x++){
			auto result = barnInventory.getItem(x, y);
			if(result.has_value()) 
				cout << result->getCode();
			else cout << "   ";
			cout << " | ";
		}
		cout << endl;
	}
}

void BreederView::detail(Breeder& breeder){
    pair<int, int> farm_size = breeder.getContext().miscConfig.getFarmSize();
    vector<pair<string, int>> list_item = {{"COW", 0}, {"SHP", 0}, {"RBT", 0}, {"HRS", 0}, {"SNK", 0}, {"CHK", 0}, {"DCK", 0}};
	vector<pair<string, string>> list_item_grid; 
    auto& barnInventory = breeder.barn;

    for(int y = 0; y < farm_size.first; y++){
        cout << "| ";
        for(int x = 0; x < farm_size.second; x++) {
            auto item = barnInventory.getItem(x, y);
            if(item.has_value() && item->getWeight() >= item->getWeightToHarvest()) {
				list_item_grid.push_back({intToCoordinate(x, y), item->getCode()});
                for(int i = 0; i < 7; ++i) {
                    if(item->getCode() == list_item[i].first) {
                        list_item[i].second++;
                        break;
                    }
                }
                //TODO: kasih kode hijau 
                cout << item->getCode();
            } else if(item.has_value() && item->getWeight() < item->getWeightToHarvest()) {
                //TODO: kasih kode merah
                cout << item->getCode(); 
            } else {
                cout << "   ";
            }
            cout << "  |  ";
        }
        cout << endl;
		std::sort(list_item.begin(), list_item.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        	return a.second > b.second; 
    	});
    }
	//validasi kalo ada yang bisa dipanen
	bool canHarvest = false; 
	for(size_t i = 0; i < list_item.size(); i++){
		if(list_item[i].second > 0){
			canHarvest = true;
		}
	}

	//print semua gridnya 
	for(size_t i = 0; i < list_item_grid.size(); i++){
		cout << "- " << list_item_grid[i].first << ": " << list_item_grid[i].second << endl;
	}

	if(canHarvest){
		int i = 1;
		cout << "Pilih hewan siap panen yang kamu miliki: " << endl; 
		vector<pair<int, pair<string, int>>> pick_list; 
		for(pair<string, int> item : list_item){
			if(item.second > 0){
				cout << i << ". " << item.first << "(" << item.second << " petak siap dipanen)" << endl;
				pick_list.push_back({i++, item}); 
			}
		}

		int no_hewan = 0; 
		while(true){
			cout << "Nomor hewan yang ingin dipanen: "; 
			cin >> no_hewan; 
			int size = pick_list.size();
			if(no_hewan > 0 &&  no_hewan <= size){
				break;
			}
			else{
				cout << "Periksa kembali nomor yang dipilih" << endl;
			}
		}
		int amount = 0; 
		while(true){
			cout << "Berapa petak yang ingin dipanen: "; 
			cin >> amount; 
			if(amount <= pick_list.at(no_hewan - 1).second.second && amount >= 0){
				break;
			}
			else{
				cout << "Jumlah hewan yang dapat dipanen lebih sedikit daripada yang ingin anda panen!" << endl;
			}

		}
		for (int j = 0; j < amount; j++)
		{
			string plot_input;
			cout << "Petak ke-" << j << ": ";
			cin >> plot_input;
			while (pick_list.at(no_hewan-1).second.first != breeder.barn.getItem(plot_input)->getCode())
			{
				cout << "Beda Hewan bang, pilih yang betul" << endl;
				cout << "Petak ke-" << j << ": ";
				cin >> plot_input;
			}
			breeder.harvestAnimal(plot_input);
		}


	}else{
		cout << "Hewan masih belum bisa dipanen" << endl; 
	}

}