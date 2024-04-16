#include "Exception/FileException.hpp"

FileException::FileException(string error) : BaseException(error){};
InvalidDirectoryFileException::InvalidDirectoryFileException() : BaseException("Direktori tidak ditemukan"){};
FileNotFoundFileException::FileNotFoundFileException(string filename) : BaseException("File " + filename + " tidak ditemukan"){};
