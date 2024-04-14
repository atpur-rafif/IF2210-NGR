#include "Exception/PlayerViewException.hpp"

const char *CommandNotFoundPlayerViewException::what() const noexcept {
	return "Perintah tidak ditemukan";
}

const char *UserCancelledPlayerViewException::what() const noexcept {
	return "Perintah dihentikan";
}

const char *ViewNotImplementedPlayerViewException ::what() const noexcept {
	return "View not implemented";
}
