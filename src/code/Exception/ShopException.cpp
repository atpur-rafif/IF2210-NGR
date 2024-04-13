#include "Exception/ShopException.hpp"

const char *NotEnoughMoneyException::what() const noexcept{
	return "Uang Anda tidak cukup untuk membeli barang ini!";
}

const char *NotEnoughInventoryException::what() const noexcept{
	return "Tempat penyimpanan Anda tidak muat!";
}

const char *NotEnoughItemException::what() const noexcept{
	return "Jumlah Item yang diminta lebih besar daripada jumlah Item yang ada!";
}

const char *InvalidSelectionException::what() const noexcept{
	return "Angka yang dimasukkan tidak valid!";
}

const char *IllegalPurchaseException::what() const noexcept{
	return "Anda tidak diizinkan membeli barang ini!";
}

const char *IllegalSalesException::what() const noexcept{
	return "Anda tidak diizinkan menjual barang ini!";
}