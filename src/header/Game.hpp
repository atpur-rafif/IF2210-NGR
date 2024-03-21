#ifndef GAME_HPP
#define GAME_HPP

#include "Item.hpp"
#include "Player.hpp"
#include "Recipe.hpp"
#include <utility>
#include <vector>

class Config {
private:
	int targetMoney;
	int targetWeight;
	pair<int, int> inventorySize;
	pair<int, int> farmSize;
	pair<int, int> barnSize;

public:
	Config(
			int targetMoney,
			int targetWeight,
			pair<int, int> inventorySize,
			pair<int, int> farmSize,
			pair<int, int> barnSize
	);
	friend istream &operator<<(istream &inputStream, Config config);
};

class Game {
private:
public:
	Game(
			vector<Player> players,
			vector<InventoryItem> inventoryItems,
			vector<FarmItem> farmItems,
			vector<BarnItem> barnItems,
			vector<Recipe> recipes
	);
};

#endif
