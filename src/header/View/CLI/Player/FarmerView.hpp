#ifndef VIEW_CLI_PLAYER_FARMER_VIEW_HPP
#define VIEW_CLI_PLAYER_FARMER_VIEW_HPP

#include "Color/pcolor.hpp"
#include "Container/Storage.hpp"
#include "Model/Player/Farmer.hpp"
#include "View/CLI/HarvesterView.hpp"
#include "View/CLI/PlayerView.hpp"

class FarmerView : public HarvesterView {
public:
	virtual ~FarmerView();
	virtual FarmerView *clone();
	virtual void runSpecializedPlayerCommand(Player &player, string command);
};

#endif
