#include "View/CLI/Player/MayorView.hpp"
#include "Exception/PlayerViewException.hpp"

MayorView::~MayorView(){};
MayorView *MayorView::clone() { return new MayorView(*this); }

void MayorView::runSpecializedPlayerCommand(Player &player, string command) {
	if (command == "PUNGUT_PAJAK") {
		(void)player;
	} else throw CommandNotFoundPlayerViewException();
}
