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
	map<string,int> collectTax();
	map<string, map<string,int>> getRecipe();

	void buildBuilding(string);
	void addPlayer(string name,string type);
	void isEnoughMoney(int money);



};


#endif
