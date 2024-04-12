#include "View/CLI/Player/BreederView.hpp"
#include "Exception/PlayerViewException.hpp"


BreederView::~BreederView(){};
BreederView *BreederView::clone() { return new BreederView(*this); }
void BreederView::runSpecializedPlayerCommand(Player &player, string command) {
	Breeder &breeder = *(dynamic_cast<Breeder *>(&player));
	if (command == "TERNAK") {
		
		string location; 
		string locationAnimal;
		BarnItem *barnItem; 
		while(true){
			this->printInventory(player); 
			location = this->promptItemFromInventory(player, barnItem); 
			this->printBarn(breeder);
			locationAnimal = this->promptFieldFromBarn(breeder);
			try
			{
				breeder.placeAnimal(locationAnimal, location);
				break;
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			
		}

	}
	else if (command == "KASIH_MAKAN"){
		string loc; 
		string locFood; 
		ProductItem *foodItem; 	
		//Ini perintah kasih makannya
		this->printBarn(breeder);
		loc = this->promptFieldFromBarn(breeder); 
		this->printInventory(player); 
		locFood = this->promptItemFromInventory(player, foodItem);
		breeder.giveFood(locFood, loc);
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

void BreederView::detail(Breeder& breeder, vector<string>& available){
    pair<int, int> farm_size = breeder.getContext().miscConfig.getFarmSize();
    const vector<string> item_codes = {"COW", "SHP", "HRS", "RBT", "SNK", "CHK", "DCK"};
    vector<pair<string, int>> list_item = {{"COW", 0}, {"SHP", 0}, {"RBT", 0}, {"HRS", 0}, {"SNK", 0}, {"CHK", 0}, {"DCK", 0}};
    vector<pair<string, string>> list_detail;
	vector<string> availableField;
    
    auto& barnInventory = breeder.barn;

    for(int y = 0; y < farm_size.first; y++){
        cout << " | ";
        for(int x = 0; x < farm_size.second; x++) {
            auto item = barnInventory.getItem(x, y);

            if(item.has_value() && item->getWeight() >= item->getWeightToHarvest()) {
                list_detail.push_back({intToCoordinate(x, y), item->getCode()});
				availableField.push_back(intToCoordinate(x, y));
                for(int i = 0; i < 7; ++i) {
                    if(item->getCode() == item_codes[i]) {
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
                cout << " ";
            }
            cout << "| ";
        }
        cout << endl;
		for(const string &item : availableField){
			available.push_back(item);
		}
    }

    // Map item codes to their corresponding names
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

    for(size_t i = 0; i < item_codes.size(); ++i) {
        if(list_item[i].second > 0) {
            cout << i + 1 << ". " << item_names[item_codes[i]] << " (" << list_item[i].second << " petak siap dipanen)" << endl;
        }
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
			else cout << " ";
			cout << " | ";
		}
		cout << endl;
	}
}
