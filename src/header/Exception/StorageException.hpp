#ifndef EXCEPTION_STORAGEEXCEPTION_HPP
#define EXCEPTION_STORAGEEXCEPTION_HPP

#include "Exception/GameException.hpp"
using namespace std;

class StorageException : public GameException {};

class InvalidItemNotFoundException : public StorageException{
public: 
	const char *what() const noexcept override;
};
class InvalidCoordinateStorageException : public StorageException {
public:
	const char *what() const noexcept override;
};

class InvalidTypeValueException : public StorageException{
public: 
	const char *what() const noexcept override;
};

class InvalidBarnEmpty : public StorageException {
public: 
	const char *what() const noexcept override;
};

class InvalidTypeException : public StorageException {
public: 
	const char *what() const noexcept override; 
};

class InvalidNotFoodException : public StorageException {
public:
	const char *what() const noexcept override; 
};

class InvalidFoodHerbivores : public StorageException {
public: 
	const char *what() const noexcept override; 
};

class InvalidFoodCarnivores : public StorageException{
public: 
	const char *what() const noexcept override; 
};

class InvalidBarnProductNotFoundException : public StorageException{
public: 
	const char *what() const noexcept override; 
};

class InvalidHarvestException : public StorageException {
public: 
	const char *what() const noexcept override; 
};

#endif