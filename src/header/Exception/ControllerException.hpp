#ifndef EXCEPTION_CONTROLLEREXCEPTION_HPP
#define EXCEPTION_CONTROLLEREXCEPTION_HPP

#include "Exception/GameException.hpp"
using namespace std;

class ControllerException : public GameException {};

class MismatchObjectTypeException : public ControllerException {
public:
	const char *what() const noexcept override;
};

#endif