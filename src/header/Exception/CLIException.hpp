#ifndef EXCEPTION_PLAYERVIEWEXCEPTION_HPP
#define EXCEPTION_PLAYERVIEWEXCEPTION_HPP

#include "Exception/GameException.hpp"
using namespace std;

class CLIException : public BaseException {
public:
	CLIException(string error);
};

class CommandNotFoundCLIException : public CLIException {
public:
	CommandNotFoundCLIException();
};

class UserCancelledCLIException : public CLIException {
public:
	UserCancelledCLIException();
};

#endif
