#ifndef MODEL_PLAYER_MAYOR_HPP
#define MODEL_PLAYER_MAYOR_HPP

#include "Model/Player.hpp"

class Mayor : public Player {
public:
	Mayor();
	virtual Mayor *clone();
	virtual ~Mayor();

	virtual int calculateTax();
};

#endif
