#ifndef EXCEPTION_BASEEXCEPTION_HPP
#define EXCEPTION_BASEEXCEPTION_HPP

#include <exception>
#include <string>
using namespace std;

class BaseException : public exception {
protected:
	string error;

public:
	BaseException();
	BaseException(string error);
	virtual const char *what() const noexcept override;
};

#endif
