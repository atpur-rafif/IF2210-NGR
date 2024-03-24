#ifndef CLI_HPP
#define CLI_HPP

#include "Game.hpp"
#include "Item.hpp"
#include <fstream>

class Config {
public:
	// TODO: seperate state reader
	static void readConfig(
			string dir,
			MiscConfig &miscConfig,
			PlayerController &players,
			ItemController<InventoryItem> &inventoryItems,
			ItemController<FarmItem> &farmItems,
			ItemController<BarnItem> &barnItems,
			ItemController<RecipeItem> &recipeItems
	);
};

#endif
