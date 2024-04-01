#ifndef EXCEPTION_PLAYERVIEWEXCEPTION_HPP
#define EXCEPTION_PLAYERVIEWEXCEPTION_HPP

#include <exception>
using namespace std;

class PlayerViewException : public exception {};

class CommandNotFoundPlayerViewException : public PlayerViewException {
public:
	const char *what() const noexcept override {
		return "Command not found";
	}
};

class UserCancelledPlayerViewException : public PlayerViewException {
public:
	const char *what() const noexcept override {
		return "Command cancelled";
	}
};

#endif
