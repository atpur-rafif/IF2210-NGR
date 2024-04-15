#ifndef VIEW_CLI_PLAYER_BREEDER_VIEW_HPP
#define VIEW_CLI_PLAYER_BREEDER_VIEW_HPP

#include "Color/pcolor.hpp"
#include "Model/Player/Breeder.hpp"
#include "View/CLI/HarvesterView.hpp"
#include "View/CLI/PlayerView.hpp"

class BreederView : public HarvesterView {
public:
	virtual ~BreederView();
	virtual BreederView *clone();
	virtual void runSpecializedPlayerCommand(Player &player, string command);
	static void feed(Breeder &breeder);
};

#endif
