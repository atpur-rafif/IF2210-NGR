#ifndef EXCEPTION_GAMEEXCEPTION_HPP
#define EXCEPTION_GAMEEXCEPTION_HPP

#include "Exception/BaseException.hpp"
#include <exception>
#include <string>
using namespace std;

class GameException : public BaseException {
public:
	GameException();
	GameException(string error);
};

class EndGameException : public GameException {
public:
	EndGameException(string reason);
};

#endif
