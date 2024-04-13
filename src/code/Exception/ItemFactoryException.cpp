#include "Exception/ItemFactoryException.hpp"

const char *ItemNotFoundException::what() const noexcept {
	return "Item not found";
}

const char *InvalidFarmProductNotFoundException::what() const noexcept{
	return "Farm product not found";
}