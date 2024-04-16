#ifndef EXCEPTION_FILEEXCEPTION_HPP
#define EXCEPTION_FILEEXCEPTION_HPP

#include "Exception/BaseException.hpp"

class FileException : public BaseException {
public:
	FileException(string error);
};

class InvalidDirectoryFileException : public BaseException {
public:
	InvalidDirectoryFileException();
};

class FileNotFoundFileException : public BaseException {
public:
	FileNotFoundFileException(string filename);
};

#endif
