#include "Exception/PlayerControllerException.hpp"

const char *InvalidPlayerTypeException::what() const noexcept {
	return "Invalid Player Type";
}