#include "Exception/CLIException.hpp"

CLIException::CLIException(string error) : BaseException(error){};
CommandNotFoundCLIException::CommandNotFoundCLIException() : CLIException("Perintah tidak ditemukan"){};
UserCancelledCLIException::UserCancelledCLIException() : CLIException("Perintah dihentikan"){};
ExitCLIException::ExitCLIException() : CLIException("Keluar dari permainan"){};
