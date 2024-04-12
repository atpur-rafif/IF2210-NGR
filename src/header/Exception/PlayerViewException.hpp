#ifndef EXCEPTION_PLAYERVIEWEXCEPTION_HPP
#define EXCEPTION_PLAYERVIEWEXCEPTION_HPP

#include "Exception/GameException.hpp"
using namespace std;

class PlayerViewException : public GameException {};

class CommandNotFoundPlayerViewException : public PlayerViewException {
public:
	const char *what() const noexcept override;
};

class UserCancelledPlayerViewException : public PlayerViewException {
public:
	const char *what() const noexcept override;
};

class ViewNotImplementedPlayerViewException : public PlayerViewException {
public:
	const char *what() const noexcept override;
};

#endif