#include "View/CLI/Player/FarmerView.hpp"
#include "Exception/PlayerViewException.hpp"
#include "Model/Player/Farmer.hpp"

FarmerView::~FarmerView(){};
FarmerView *FarmerView::clone() { return new FarmerView(*this); }

void FarmerView::runSpecializedPlayerCommand(Player &player, string command) {
	Farmer *farmer = dynamic_cast<Farmer *>(&player);
	if (command == "TEST") {
		auto &inventory = farmer->farm;
		auto size = inventory.getSize();
		for (int y = 0; y < size.second; ++y) {
			cout << "| ";
			for (int x = 0; x < size.first; ++x) {
				auto result = inventory.getItem(x, y);
				if (result.has_value()) cout << result->getCode();
				else cout << "   ";
				cout << " | ";
			}
			cout << endl;
		}

	} else throw CommandNotFoundPlayerViewException();
}
