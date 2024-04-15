#ifndef MODEL_HARVESTABLE_HPP
#define MODEL_HARVESTABLE_HPP

#include "Model/Item.hpp"

class Harvestable : public Item {
public:
	virtual bool harvestable() = 0;
	virtual void readHarvestState(istream &inputStream) = 0;
	virtual void writeHarvestState(ostream &outputStream) = 0;
};

#endif
