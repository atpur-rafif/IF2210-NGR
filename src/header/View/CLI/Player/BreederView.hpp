#ifndef VIEW_CLI_PLAYER_BREEDER_VIEW_HPP
#define VIEW_CLI_PLAYER_BREEDER_VIEW_HPP

#include "View/CLI/PlayerView.hpp"
#include "Model/Player/Breeder.hpp"

class BreederView : public PlayerView {
public:
	virtual ~BreederView();
	virtual BreederView *clone();
	virtual void runSpecializedPlayerCommand(Player &player, string command);
	virtual void printBarn(Breeder &breeder);
	virtual void detail(Breeder &breeder, vector<string>&); 

	string promptFieldFromBarn(Breeder& breeder){
		while(true){
			cout << "Pilih petak tanah yang ditinggal: "; 
			string loc; 
			cin >> loc; 

			if(loc == "CANCEL"){
				throw UserCancelledPlayerViewException();
			}
			try{
				auto rawField = breeder.barn.getItem(loc);
				if(rawField.has_value()){
					cout << "Petak sudah terisi" << endl;
					continue;
				}
				else{
					return loc;
				}
			}catch(const exception& e){
				cout << e.what() << endl;
			}
		}
	}
	
	static string intToString(int value) {
    string result = "";
    while (value > 0) {
        result = char((value % 26) + 'A') + result;
        value /= 26;
    }
    return result;
	}

	static string intToCoordinate(int x, int y) {
		if (x < 0 || y < 0) throw invalid_argument("Coordinates cannot be negative.");

		string xStr = intToString(x);
		string yStr = to_string(y + 1);

		return xStr + yStr;
	}
};

#endif
