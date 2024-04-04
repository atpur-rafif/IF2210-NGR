#ifndef EXCEPTION_PLAYERVIEWEXCEPTION_HPP
#define EXCEPTION_PLAYERVIEWEXCEPTION_HPP

#include <exception>
using namespace std;

class PlayerViewException : public exception {};

class CommandNotFoundPlayerViewException : public PlayerViewException {
public:
	const char *what() const noexcept override;
};

class UserCancelledPlayerViewException : public PlayerViewException {
public:
	const char *what() const noexcept override;
};

#endif
