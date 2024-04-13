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
		vector<string> availableField; 

		cout << "========================PETERNAKAN==============================\n";
		detail(breeder, availableField); 
		cout << "Nomor hewan yang ingin dipanen: "; 
		cin >> choose; 
		
		cout << "Berapa petak yang ingin dipanen: "; 
		cin >> total; 
		int totalField = availableField.size();
		if(int(stoi(total)) >= totalField){
			throw "LMAO"; 
		}
		string petak;	
		cout << "Pilih petak yang ingin dipanen: " << endl; 
		for(int i = 0; i < int(stoi(total));i++){
			cout << "Petak ke-" << i + 1 <<": "; 
			cin >>	petak; 
			if(std::find(availableField.begin(), availableField.end(), petak) == availableField.end()){
				throw InvalidHarvestException();
			}
			breeder.harvestAnimal(petak); 
		}
	}
	else {
		throw CommandNotFoundPlayerViewException(); 
	}

}

void BreederView::printBarn(Breeder& breeder){
	auto &barnInventory = breeder.barn; 
	pair<int, int> size = {barnInventory.getWidth(), barnInventory.getHeight()};
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

void BreederView::detail(Breeder& breeder, vector<string>& available){
    pair<int, int> farm_size = breeder.getContext().miscConfig.getFarmSize();
    vector<pair<string, int>> list_item = {{"COW", 0}, {"SHP", 0}, {"RBT", 0}, {"HRS", 0}, {"SNK", 0}, {"CHK", 0}, {"DCK", 0}};
	vector<pair<int, string>> list_item_numbered; 
    vector<pair<string, string>> list_detail;
	vector<string> availableField;
    
    auto& barnInventory = breeder.barn;

    for(int y = 0; y < farm_size.first; y++){
        cout << "| ";
        for(int x = 0; x < farm_size.second; x++) {
            auto item = barnInventory.getItem(x, y);

            if(item.has_value() && item->getWeight() >= item->getWeightToHarvest()) {
                list_detail.push_back({intToCoordinate(x, y), item->getCode()});
				availableField.push_back(intToCoordinate(x, y));
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
		sort(list_item.begin(), list_item.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        	return a.second > b.second; 
    	});
		for(const string &item : availableField){
			available.push_back(item);
		}
		int idx = 1;
		for(size_t i = 0; i < list_item.size() ; i++){
			list_item_numbered.push_back({idx++, list_item[i].first});
		}
    }

    map<string, string> item_names = {
        {"COW", "Cow"},
        {"SHP", "Sheep"},
        {"HRS", "Horse"},
        {"RBT", "Rabbit"},
        {"SNK", "Snake"},
        {"CHK", "Chicken"},
        {"DCK", "Duck"}
    };

    for(const auto& detail : list_detail) {
        cout << "- " << detail.first << ": " << item_names[detail.second] << endl;
    }

    for(size_t i = 0; i < availableField.size(); ++i) {
        if(list_item[i].second > 0){
            cout << i + 1 << ". " << list_item_numbered[i].second << " (" << list_item[i].second << " petak siap dipanen)" << endl;
        }
    }
}

