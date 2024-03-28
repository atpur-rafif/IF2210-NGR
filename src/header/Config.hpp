#ifndef CLI_HPP
#define CLI_HPP

#include "Game.hpp"
#include "Item.hpp"

class Config {
public:
	// TODO: seperate state reader
	static void readConfig(
			string dir,
			MiscConfig &miscConfig,
			PlayerController &players,
			ItemFactory<ProductItem> &productFactory,
			ItemFactory<FarmItem> &farmFactory,
			ItemFactory<BarnItem> &barnFactory,
			ItemFactory<RecipeItem> &recipeFactory
	);
};

#endif
