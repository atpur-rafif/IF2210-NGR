#include "Exception/StorageException.hpp"

const char *InvalidItemNotFoundException::what() const noexcept{
	return "Item not found";
}

const char *InvalidCoordinateStorageException::what() const noexcept {
	return "Invalid coordinate";
}

const char *InvalidTypeValueException::what() const noexcept {
	return "Invalid type";
}

const char *InvalidBarnEmpty::what() const noexcept{
	return "Barn are empty";
}

const char *InvalidTypeException::what() const noexcept{
	return "Invalid food type";
}

const char *InvalidNotFoodException::what() const noexcept{
	return "Invalid food";
}

const char *InvalidFoodHerbivores::what() const noexcept{
	return "Herbivores eat fruit product";
}

const char *InvalidFoodCarnivores::what() const noexcept{
	return "Herbivores eat animal product";
}

const char *InvalidBarnProductNotFoundException::what() const noexcept{
	return "Product not found";
}

const char *InvalidHarvestException::what() const noexcept{
	return "Petak tidak bisa dipanen";
}