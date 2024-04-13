#ifndef EXCEPTION_ITEMFACTORYEXCEPTION_HPP
#define EXCEPTION_ITEMFACTORYEXCEPTION_HPP

#include "Exception/GameException.hpp"
using namespace std;

class ItemFactoryException : public GameException {};

class ItemNotFoundException : public ItemFactoryException {
public:
	const char *what() const noexcept override;
	
};

class InvalidFarmProductNotFoundException : public ItemFactoryException{
public: 
	const char *what() const noexcept override; 
};

#endif