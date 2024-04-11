#ifndef EXCEPTION_DOWNCASTEXCEPTION_HPP
#define EXCEPTION_DOWNCASTEXCEPTION_HPP

#include "Exception/GameException.hpp"
using namespace std;

class DowncastException : public GameException {};

class InvalidDowncastException : public DowncastException {
public:
	const char *what() const noexcept override;
};

#endif