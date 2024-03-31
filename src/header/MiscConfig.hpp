#ifndef MISCCONFIG_HPP
#define MISCCONFIG_HPP

#include <iostream>
#include <utility>
using namespace std;
class MiscConfig {
	friend class GameContext;

protected:
	MiscConfig();
	int targetMoney;
	int targetWeight;
	pair<int, int> inventorySize;
	pair<int, int> farmSize;
	pair<int, int> barnSize;

public:
	int getTargetMoney();
	int getTargetWeight();
	pair<int, int> getInventorySize();
	pair<int, int> getFarmSize();
	pair<int, int> getBarnSize();
	friend istream &operator>>(istream &inputStream, MiscConfig &miscConfig);
};

#endif
