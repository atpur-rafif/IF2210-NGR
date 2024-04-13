#include "Exception/ConfigException.hpp"

const char *InvalidDirectoryConfigException::what() const noexcept {
	return "Directory not found";
};

FileNotFoundConfigException::FileNotFoundConfigException(string filename) : error("File " + filename + " not found"){};

const char *FileNotFoundConfigException::what() const noexcept {
	return this->error.c_str();
};
