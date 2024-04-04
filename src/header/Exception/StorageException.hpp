#ifndef EXCEPTION_STORAGEEXCEPTION_HPP
#define EXCEPTION_STORAGEEXCEPTION_HPP

#include "Exception/GameException.hpp"
using namespace std;

class StorageException : public GameException {};

class InvalidCoordinateStorageException : public StorageException {
public:
	const char *what() const noexcept override;
};

#endif
