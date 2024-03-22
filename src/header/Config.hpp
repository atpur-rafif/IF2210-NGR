#ifndef CLI_HPP
#define CLI_HPP

#include "Game.hpp"
#include "Item.hpp"
#include <fstream>

class Config {
public:
	static void readConfig(
			string dir,
			MiscConfig &miscConfig,
			vector<Player *> &players,
			vector<InventoryItem> &inventoryItems,
			vector<FarmItem> &farmItems,
			vector<BarnItem> &barnItems,
			vector<RecipeItem> &recipes
	);
};

#endif
