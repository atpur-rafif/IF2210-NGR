#ifndef VIEW_CLI_PLAYER_FARMER_VIEW_HPP
#define VIEW_CLI_PLAYER_FARMER_VIEW_HPP

#include "View/CLI/PlayerView.hpp"
#include "Model/Player/Farmer.hpp"
#include "Container/Storage.hpp"

class FarmerView : public PlayerView {
public:
	virtual ~FarmerView();
	virtual FarmerView *clone();
	virtual void runSpecializedPlayerCommand(Player &player, string command);
	void printFarm(Farmer &farmer);
	void plantHelper(Farmer &farmer);
	void harvestHelper(Farmer &farmer);

	string promptFieldFromFarm(Farmer &farmer) {
		while (true) {
			cout << "Petak: ";
			string location;
			cin >> location;
			if (location == "CANCEL")
				throw UserCancelledPlayerViewException();
			try {
				auto rawItem = farmer.farm.getItem(location);
				if (rawItem.has_value()) {
					cout << "Petak sudah terisi" << endl;
					continue;
				}
				else
				{
					return location;
				}

			} catch (const exception &err) {
				cout << err.what() << endl;
			}
		}
	}
};

#endif