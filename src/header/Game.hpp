#ifndef GAME_HPP
#define GAME_HPP

#include "Item.hpp"
#include "Player.hpp"
#include "Recipe.hpp"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class Config {
	int targetMoney;
	int targetWeight;
	pair<int, int> inventorySize;
	pair<int, int> farmSize;
	pair<int, int> barnSize;

public:
	Config();
	Config(
			int targetMoney,
			int targetWeight,
			pair<int, int> inventorySize,
			pair<int, int> farmSize,
			pair<int, int> barnSize
	);
	int getTargetMoney();
	int getTargetWeight();
	pair<int, int> getInventorySize();
	pair<int, int> getFarmSize();
	pair<int, int> getBarnSize();
	friend istream &operator>>(istream &inputStream, Config &config);
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
