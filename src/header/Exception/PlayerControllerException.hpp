#ifndef EXCEPTION_PLAYERCONTROLLEREXCEPTION_HPP
#define EXCEPTION_PLAYERCONTROLLEREXCEPTION_HPP

#include "Exception/GameException.hpp"
using namespace std;

class PlayerControllerException : public GameException {};

class InvalidPlayerTypeException : public PlayerControllerException {
public:
	const char *what() const noexcept;
};

class UsernameAlreadyExist : public PlayerControllerException {
public:
	const char *what() const noexcept;
};

#endif