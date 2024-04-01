#ifndef VIEW_CLI_PLAYER_MAYOR_VIEW_HPP
#define VIEW_CLI_PLAYER_MAYOR_VIEW_HPP

#include "View/CLI/PlayerView.hpp"

class MayorView : public PlayerView {
public:
	virtual ~MayorView();
	virtual MayorView *clone();
	virtual void runSpecializedPlayerCommand(Player &player, string command);
};

#endif
