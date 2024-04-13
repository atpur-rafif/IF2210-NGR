#include "Exception/ItemFactoryException.hpp"

const char *ItemNotFoundException::what() const noexcept {
	return "Item not found";
}