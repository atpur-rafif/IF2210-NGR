#include "View/CLI/Player/MayorView.hpp"
#include "Exception/PlayerViewException.hpp"
#include "Model/Player.hpp"
#include "Model/Player/Mayor.hpp"

MayorView::~MayorView(){};
MayorView *MayorView::clone() { return new MayorView(*this); }

void MayorView::runSpecializedPlayerCommand(Player &player, string command) {
	Mayor &mayor = *(dynamic_cast<Mayor *>(&player));
	if (command == "PUNGUT_PAJAK") mayor.collectTax();
	else throw CommandNotFoundPlayerViewException();
}
