#include "View/CLI/Player/BreederView.hpp"
#include "Exception/PlayerViewException.hpp"

BreederView::~BreederView(){};
BreederView *BreederView::clone() { return new BreederView(*this); }
void BreederView::runSpecializedPlayerCommand(Player &player, string command) {
	if (command == "TERNAK") {
		(void)player;
	} else throw CommandNotFoundPlayerViewException();
}
