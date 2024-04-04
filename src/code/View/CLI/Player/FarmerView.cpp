#include "View/CLI/Player/FarmerView.hpp"
#include "Exception/PlayerViewException.hpp"

FarmerView::~FarmerView(){};
FarmerView *FarmerView::clone() { return new FarmerView(*this); }

void FarmerView::runSpecializedPlayerCommand(Player &player, string command) {
	if (command == "TANAM") {
		(void)player;
	} else throw CommandNotFoundPlayerViewException();
}
