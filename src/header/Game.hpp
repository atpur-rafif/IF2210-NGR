#ifndef GAME_HPP
#define GAME_HPP

#include "Item.hpp"
#include "Player.hpp"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class MiscConfig {
	int targetMoney;
	int targetWeight;
	pair<int, int> productSize;
	pair<int, int> farmSize;
	pair<int, int> barnSize;

public:
	MiscConfig();
	MiscConfig(
			int targetMoney,
			int targetWeight,
			pair<int, int> productSize,
			pair<int, int> farmSize,
			pair<int, int> barnSize
	);
	int getTargetMoney();
	int getTargetWeight();
	pair<int, int> getProductSize();
	pair<int, int> getFarmSize();
	pair<int, int> getBarnSize();
	friend istream &operator>>(istream &inputStream, MiscConfig &miscConfig);
};

class Game {
private:
public:
	Game();
};

#endif
