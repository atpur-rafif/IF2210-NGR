#include "Exception/DowncastException.hpp"

const char *InvalidDowncastException::what() const noexcept {
	return "Invalid Downcast";
}