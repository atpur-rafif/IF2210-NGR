#include "View/CLI/Player/BreederView.hpp"
#include "Exception/PlayerViewException.hpp"
#include <algorithm>
#include <limits>


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
	else if (command == "CETAK_PETERNAKAN"){
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

/** ISSUE: 
 *  ada yang dia cuman satu tapi kecetak dua, misal di A1 ada DCK (kenyataannya begitu), tapi pas dicetak somehov muncul 
 * 	beberapa kali di F2 (misalnya) dia muncul DCK juga.
*/
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
    pair<int, int> farm_size = breeder.barn.getSize();
    vector<pair<string, int>> list_item = {{"COW", 0}, {"SHP", 0}, {"RBT", 0}, {"HRS", 0}, {"SNK", 0}, {"CHK", 0}, {"DCK", 0}};
	vector<pair<string, string>> list_item_grid; 
    auto& barnInventory = breeder.barn;

    for(int y = 0; y < farm_size.first; y++){
        cout << "| ";
        for(int x = 0; x < farm_size.second; x++) {
            auto item = barnInventory.getItem(x, y);
            if(item.has_value() && item.value().getWeight() >= item.value().getWeightToHarvest()) {
				// cout << item.value().getWeight() << " " << item.value().getWeightToHarvest();
				list_item_grid.push_back({intToCoordinate(x, y), item->getName()});
                for(int i = 0; i < 7; ++i) {
                    if(item->getCode() == list_item[i].first) {
                        list_item[i].second++;
                        break;
                    }
                }
                /**
				 * TODO: 
				 * kasih kode hijau  kalo bisa diharvest
				 */
                cout << item->getCode();
            } else if(item.has_value() && item->getWeight() < item->getWeightToHarvest()) {
                /**
				 * TODO: kasih kode merah kalo gabisa diharvest
				*/
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
		bool invalidInput = false;
		while(true){
			if (invalidInput) {
				cout << "Periksa kembali nomor yang dipilih" << endl;
				invalidInput = false; 
			}
			cout << "Nomor hewan yang ingin dipanen: "; 
			cin >> no_hewan; 
			int size = pick_list.size();
			if(cin.fail()){
				cout << "Input harus berupa bilangan bulat.\n"; 
				cin.clear(); 
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			if (no_hewan > 0 &&  no_hewan <= size) {
				break;
			} else {
				invalidInput = true; 
			} 
			
		}
		int amount = 0; 
		bool isValid = false;
		while(true){
			cout << "Berapa petak yang ingin dipanen: "; 
			cin >> amount; 
        	if (cin.fail()) {
				cout << "Input harus sebuah angka." << endl;
				cin.clear(); 
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
				continue;
        	}
			if(amount <= pick_list.at(no_hewan - 1).second.second && amount >= 0){
				isValid = true;
				break;
			}
			else if (amount > pick_list.at(no_hewan - 1).second.second && amount >= 0){
				cout << "Jumlah hewan yang dapat dipanen lebih sedikit daripada yang ingin anda panen!" << endl;
				continue;
			}
			else{
				cout << "Input tidak valid" << endl; 
				continue;
			}

		}
		if(isValid){
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
		}	
		else{
			cout << "Input tidak Valid, Keluar dari perintah PANEN secara paksa"; 
		}


	}else{
		cout << "Hewan masih belum bisa dipanen" << endl; 
	}

}