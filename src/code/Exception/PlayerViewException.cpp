#include "Exception/PlayerViewException.hpp"

const char *CommandNotFoundPlayerViewException::what() const noexcept {
	return "Command not found";
}

const char *UserCancelledPlayerViewException::what() const noexcept {
	return "Command cancelled";
}

const char *ViewNotImplementedPlayerViewException ::what() const noexcept {
	return "View not implemented";
}