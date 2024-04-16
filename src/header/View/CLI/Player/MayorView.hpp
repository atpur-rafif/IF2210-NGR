#ifndef VIEW_CLI_PLAYER_MAYOR_VIEW_HPP
#define VIEW_CLI_PLAYER_MAYOR_VIEW_HPP

#include "Model/Player/Mayor.hpp"
#include "View/CLI/PlayerView.hpp"

class MayorView : public PlayerView {
public:
	virtual ~MayorView();
	virtual MayorView *clone();
	virtual void runSpecializedPlayerCommand(Player &player, string command);

	static void collectTax(Mayor &mayor);
	static void build(Mayor &mayor);
	static void addPlayer(Mayor &mayor);
};

#endif
