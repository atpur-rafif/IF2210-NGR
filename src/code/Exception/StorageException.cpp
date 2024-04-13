#include "Exception/StorageException.hpp"

const char *InvalidItemNotFoundException::what() const noexcept{
	return "Item not found";
}

const char *InvalidFoodNotFoundException::what() const noexcept{
	return "Food for this animal isn't exists in inventory";
}

const char *InvalidCoordinateStorageException::what() const noexcept {
	return "Invalid coordinate";
}

const char *InvalidTypeValueException::what() const noexcept {
	return "Invalid type";
}

const char *InvalidFieldEmptyException::what() const noexcept{
	return "Field are empty";
}

const char *InvalidNotFoodException::what() const noexcept{
	return "Invalid food type";
}

const char *InvalidFoodHerbivores::what() const noexcept{
	return "Herbivores eat fruit product";
}

const char *InvalidFoodCarnivores::what() const noexcept{
	return "Herbivores eat animal product";
}

const char *InvalidHarvestException::what() const noexcept{
	return "Petak tidak bisa dipanen";
}