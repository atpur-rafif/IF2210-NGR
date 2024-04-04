#include "Exception/StorageException.hpp"

const char *InvalidCoordinateStorageException::what() const noexcept {
	return "Invalid coordinate";
};
