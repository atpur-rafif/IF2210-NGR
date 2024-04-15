#include "Exception/GameException.hpp"
GameException::GameException() : BaseException(){};
GameException::GameException(string error) : BaseException(error){};
