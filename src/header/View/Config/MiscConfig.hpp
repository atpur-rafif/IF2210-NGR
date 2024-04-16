#ifndef VIEW_MISCCONFIG_HPP
#define VIEW_MISCCONFIG_HPP

#include <iostream>
#include <utility>
using namespace std;
class MiscConfig {
	friend class GameContext;

protected:
	MiscConfig();
	int targetMoney;
	int targetWeight;

	int inventoryWidth;
	int inventoryHeight;

	int farmWidth;
	int farmHeight;

	int barnWidth;
	int barnHeight;

public:
	int getTargetMoney();
	int getTargetWeight();

	int getInventoryWidth();
	int getFarmWidth();
	int getBarnWidth();

	int getInventoryHeight();
	int getFarmHeight();
	int getBarnHeight();

	friend istream &operator>>(istream &inputStream, MiscConfig &miscConfig);
};

#endif
