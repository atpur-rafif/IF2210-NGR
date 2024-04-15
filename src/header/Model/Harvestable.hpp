#ifndef MODEL_HARVESTABLE_HPP
#define MODEL_HARVESTABLE_HPP

#include "Model/GameObject.hpp"

class Harvestable : virtual public GameObject {
public:
	virtual bool harvestable() = 0;
};

#endif
