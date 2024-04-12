#ifndef EXCEPTION_SHOPEXCEPTION_HPP
#define EXCEPTION_SHOPEXCEPTION_HPP

#include "Exception/GameException.hpp"
using namespace std;

class ShopException : public GameException {};

class NotEnoughMoneyException : public ShopException{
public: 
	const char *what() const noexcept override;
};

class NotEnoughInventoryException : public ShopException{
public: 
	const char *what() const noexcept override;
};

class IllegalPurchaseException : public ShopException{
public: 
	const char *what() const noexcept override;
};

class IllegalSalesException : public ShopException{
public: 
	const char *what() const noexcept override;
};

#endif