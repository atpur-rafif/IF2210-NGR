#ifndef MODEL_PLAYER_MAYOR_HPP
#define MODEL_PLAYER_MAYOR_HPP

#include "Model/Player.hpp"
#include <map>

class Mayor : public Player {
public:
	Mayor();
	virtual Mayor *clone();
	virtual ~Mayor();

	virtual int calculateTax();
	vector<pair<shared_ptr<Player>, int>> collectTax();
	void getRecipe(map<string, map<string, int>> &recipe);

	void buildBuilding(string);
	void addPlayer(string name, string type);
	void isEnoughMoney();

	virtual void readSpecializedConfig(istream &inputStream);
};

#endif
