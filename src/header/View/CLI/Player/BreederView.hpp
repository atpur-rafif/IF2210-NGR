#ifndef VIEW_CLI_PLAYER_BREEDER_VIEW_HPP
#define VIEW_CLI_PLAYER_BREEDER_VIEW_HPP

#include "Color/pcolor.hpp"
#include "Model/Player/Breeder.hpp"
#include "View/CLI/PlayerView.hpp"

class BreederView : public PlayerView {
public:
	virtual ~BreederView();
	virtual BreederView *clone();
	virtual void runSpecializedPlayerCommand(Player &player, string command);

	static void printBarn(Breeder &breeder);
	static void breed(Breeder &breeder);
	static void feed(Breeder &breeder);
	static void harvest(Breeder &breeder);

	// TODO: Benerin
	static string promptFieldFromBarn(Breeder &breeder, string msg, bool taruhHewan) {
		while (true) {
			cout << msg;
			string loc;
			cin >> loc;

			auto rawField = breeder.getBarn().getItem(loc);
			if (loc == "CANCEL") {
				throw UserCancelledPlayerViewException();
			}
			if (taruhHewan) {
				try {
					if (rawField.has_value()) {
						cout << "Petak sudah terisi" << endl;
						continue;
					} else {
						return loc;
					}
				} catch (const exception &e) {
					cout << e.what() << endl;
				}
			} else {
				try {
					if (!rawField.has_value()) {
						cout << "Petak kosong ngapain dikasih makan" << endl;
						continue;
					} else {
						return loc;
					}
				} catch (const std::exception &e) {
					std::cerr << e.what() << '\n';
				}
			}
		}
	}

	static string intToString(int value) {
		string result = "";
		while (value >= 0) {
			result = char((value % 26) + 'A') + result;
			value /= 26;
			if (value == 0) {
				break;
			}
			value--;
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
