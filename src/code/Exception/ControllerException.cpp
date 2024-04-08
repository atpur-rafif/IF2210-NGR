#include "Exception/ControllerException.hpp"

const char *MismatchObjectTypeException::what() const noexcept {
	return "Object type did not match";
}