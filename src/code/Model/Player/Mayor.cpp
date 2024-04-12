#include "Model/Player/Mayor.hpp"
#include "Controller/GameContext.hpp"

Mayor::Mayor() { this->type = MayorType; }
Mayor::~Mayor() {}
Mayor *Mayor::clone() { return new Mayor(*this); }

void Mayor::collectTax() {
	auto players = this->getContext().players.getPlayers();
	int size = players.size();
	for (int i = 0; i < size; ++i) {
		auto &income = players[i];
		if (income->type == MayorType) continue;
		int tax = income->calculateTax();
		income->money -= tax;
		this->money += tax;
		cout << income->username << " " << tax << endl;
	}
}

int Mayor::calculateTax() {
	return 0;
}
