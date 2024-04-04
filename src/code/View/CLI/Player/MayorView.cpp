#include "View/CLI/Player/MayorView.hpp"
#include "Controller/GameContext.hpp"
#include "Exception/PlayerViewException.hpp"
#include "Model/Player.hpp"

MayorView::~MayorView(){};
MayorView *MayorView::clone() { return new MayorView(*this); }

void MayorView::runSpecializedPlayerCommand(Player &player, string command) {
	if (command == "PUNGUT_PAJAK") {
		auto &players = *player.getContext().players.getPlayers();
		int size = players.size();
		for (int i = 0; i < size; ++i) {
			auto &income = players[i];
			if (income->type == MayorType) continue;
			int tax = income->calculateTax();
			income->money -= tax;
			player.money += tax;
			cout << income->username << " " << tax << endl;
		}
	} else throw CommandNotFoundPlayerViewException();
}
