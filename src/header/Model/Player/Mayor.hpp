#ifndef MODEL_PLAYER_MAYOR_HPP
#define MODEL_PLAYER_MAYOR_HPP

#include "Model/Item/BuildingItem.hpp"
#include "Model/Player.hpp"
#include <map>

class Mayor : public Player {
public:
	Mayor();
	virtual Mayor *clone();
	virtual ~Mayor();

	virtual int calculateTax();
	vector<pair<shared_ptr<Player>, int>> collectTax();

	void buildBuilding(string name, vector<string> &ingredientLocation);
	void addPlayer(string name, string type);
	void isEnoughMoney();
	pair<vector<string>, map<string, int>> checkInventory(map<string, int> items);

	virtual void readSpecializedConfig(istream &inputStream);
	virtual void writeSpecializedConfig(ostream &outputStream);
};

#endif
