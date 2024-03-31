#include "Model/Player/Mayor.hpp"

Mayor::Mayor() { this->type = MayorType; }
Mayor::~Mayor() {}
Mayor *Mayor::clone() { return new Mayor(*this); }

int Mayor::calculateTax() {
	return 0;
}
