#ifndef VIEW_CLI_PLAYER_BREEDER_VIEW_HPP
#define VIEW_CLI_PLAYER_BREEDER_VIEW_HPP

#include "View/CLI/PlayerView.hpp"

class BreederView : public PlayerView {
public:
	virtual ~BreederView();
	virtual BreederView *clone();
	virtual void runSpecializedPlayerCommand(Player &player, string command);
};

#endif
