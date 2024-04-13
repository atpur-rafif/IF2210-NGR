#ifndef EXCEPTION_CONFIGEXCEPTION_HPP
#define EXCEPTION_CONFIGEXCEPTION_HPP

#include "Exception/GameException.hpp"
#include <string>

class ConfigException : public GameException {};

class InvalidDirectoryConfigException : public ConfigException {
public:
	const char *what() const noexcept override;
};

class FileNotFoundConfigException : public ConfigException {
public:
	string error;
	FileNotFoundConfigException(string filename);
	const char *what() const noexcept override;
};

#endif
