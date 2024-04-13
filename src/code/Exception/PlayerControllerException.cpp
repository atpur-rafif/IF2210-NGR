#include "Exception/PlayerControllerException.hpp"

const char *InvalidPlayerTypeException::what() const noexcept {
	return "Invalid Player Type";
}

const char *UsernameAlreadyExist::what() const noexcept {
	return "Username already exist";
}
