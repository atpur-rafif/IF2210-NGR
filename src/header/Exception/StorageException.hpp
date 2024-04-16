#ifndef EXCEPTION_STORAGEEXCEPTION_HPP
#define EXCEPTION_STORAGEEXCEPTION_HPP

#include "Exception/GameException.hpp"
using namespace std;

class InvalidCoordinateStorageException : public BaseException {
public:
	InvalidCoordinateStorageException();
};

#endif
