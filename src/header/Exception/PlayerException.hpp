#ifndef EXCEPTION_PLAYEREXCEPTION_HPP
#define EXCEPTION_PLAYEREXCEPTION_HPP

#include "Exception/GameException.hpp"
#include <string>
#include <map>
using namespace std;

class PlayerException : public GameException {};

class NotEnoughResourceException : public PlayerException {
private:
    string message;
public:
    NotEnoughResourceException(map<string,int> &remainingResource, int &remainingMoney);
    NotEnoughResourceException(void);
	const char *what() const noexcept;
};

#endif
