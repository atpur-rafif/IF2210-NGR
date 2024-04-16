#include "Exception/BaseException.hpp"

BaseException::BaseException() : BaseException(""){};
BaseException::BaseException(string error) : error(error){};

const char *BaseException::what() const noexcept {
	return this->error.c_str();
};
