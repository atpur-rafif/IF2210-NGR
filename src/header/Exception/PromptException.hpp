#ifndef EXCEPTION_PROMPTEXCEPTION_HPP
#define EXCEPTION_PROMPTEXCEPTION_HPP

#include "Exception/BaseException.hpp"

class PromptException : public BaseException {
public:
	PromptException(string error);
};

#endif
