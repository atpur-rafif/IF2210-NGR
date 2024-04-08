#include "Shop_View.hpp"
#include <iostream>
#include <string>

void ShopView::displayProducts(const std::vector<Product> &products) {
    std::cout << "Produk:\n";
    for (const auto &product : products) {
        std::cout << "Nama: " << product.name << ", Harga: " << product.price << ", Kuantitas: " << product.quantity << "\n";
    }
}

void ShopView::displayTotal(const std::vector<Product> &products) {
    double total = 0;
    for (const auto &product : products) {
        total += product.price * product.quantity;
    }
    std::cout << "Total: " << total << "\n";
}