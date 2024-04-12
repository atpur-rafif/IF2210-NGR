#include "View/CLI/Player/MayorView.hpp"
#include "Exception/PlayerViewException.hpp"
#include "Exception/DowncastException.hpp"
#include "Exception/PlayerException.hpp"
#include "Exception/ItemFactoryException.hpp"
#include "Model/Player.hpp"
#include "Model/Player/Mayor.hpp"

MayorView::~MayorView(){};
MayorView *MayorView::clone() { return new MayorView(*this); }

void MayorView::runSpecializedPlayerCommand(Player &player, string command) {
	Mayor &mayor = *(dynamic_cast<Mayor *>(&player));
	map<string,map<string,int>> recipe;
	mayor.getRecipe(recipe);
	if (command == "PUNGUT_PAJAK"){
		vector<pair<Player*,int>> pajakTerpungut = mayor.collectTax();
		int i = 0; 
		int sum = 0;
		cout << "Cring cring cring..." << endl;
		cout << "Pajak sudah dipungut!" << endl;
		cout << "Berikut adalah detil dari pemungutan pajak:" << endl;
		for(const auto& pair : pajakTerpungut){
			cout << ++i << ". " << pair.first->username << " - " << pair.first->playerTypeToString(pair.first->type) << ": " << pair.second << " gulden" << endl;
			sum += pair.second;
			}
		cout << "Negara mendapatkan pemasukan sebesar " << sum << " gulden." << endl;
		cout << "Gunakan dengan baik dan jangan dikorupsi ya!" << endl;
		}
	else if (command == "BANGUN") {
		string buildingName;
		int i = 1;
		for(auto it=recipe.cbegin(); it!=recipe.cend();++it){
			cout << i++ << ". " << it->first << " (";
			for(auto it2=it->second.cbegin();it2!=it->second.cend();++it2){
				if(it2==it->second.cbegin()) {
					cout << it->second.at("GULDEN") << " GULDEN";
					if(it->second.cbegin()!=(it->second.cend())) cout << ", "; 
				}
				if(it2->first!="GULDEN"){
				cout << it2->second << " ";
				cout << it2->first;
				if(it2!=prev(it->second.cend())) cout << ", "; 
				else cout << ")" << endl;}
			
			}
		}
		cout << "Bangunan yang ingin dibangun: ";
		cin  >> buildingName;
		try{
			mayor.buildBuilding(buildingName);
			cout << buildingName << " berhasil dibangun dan telah menjadi hak milik walikota!" << endl;
		}
		catch(const InvalidDowncastException& e){
			cout << "Kamu tidak punya resep bangunan tersebut!" << endl;
		}
		catch(const ItemNotFoundException& e){
			cout << "Kamu tidak punya resep bangunan tersebut!" << endl;
		}
		catch(const NotEnoughResourceException& e){
			cout << "Kamu tidak punya sumber daya yang cukup! Masih memerlukan " << e.what() << "!" << endl;
		}
	}
	else if (command == "TAMBAH_PEMAIN"){
		try{
			mayor.isEnoughMoney();
			string username;
			string type;
			cout << "Masukkan jenis pemain: ";
			cin  >> type ;
			cout << "Masukkan nama pemain: ";
			cin  >> username ;
			mayor.addPlayer(username,type);
			cout << "Pemain baru ditambahkan!" << endl;
			cout << "Selamat datang " << username << " di kota ini!" << endl;
		}
		catch(const char* err){
			cout << err << endl;
		}
	}
	else throw CommandNotFoundPlayerViewException();
}
