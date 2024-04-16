#include "View/CLI/Player/FarmerView.hpp"
#include "Exception/CLIException.hpp"
#include "Model/Player/Farmer.hpp"
#include "View/CLI/CLI.hpp"

FarmerView::~FarmerView(){};
FarmerView *FarmerView::clone() { return new FarmerView(*this); }

void FarmerView::runSpecializedPlayerCommand(Player &player, string command) {
	Farmer &farmer = *(dynamic_cast<Farmer *>(&player));
	if (command == "TANAM") this->place(farmer);
	else if (command == "PANEN") this->harvest(farmer);
	else if (command == "CETAK_LADANG") this->printField(farmer);
	else throw CommandNotFoundCLIException();
}
