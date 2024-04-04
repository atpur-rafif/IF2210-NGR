#ifndef VIEW_CLI_PLAYER_FARMER_VIEW_HPP
#define VIEW_CLI_PLAYER_FARMER_VIEW_HPP

#include "View/CLI/PlayerView.hpp"

class FarmerView : public PlayerView {
public:
	virtual ~FarmerView();
	virtual FarmerView *clone();
	virtual void runSpecializedPlayerCommand(Player &player, string command);
};

#endif
