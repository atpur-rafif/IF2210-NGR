#ifndef SHOP_VIEW_HPP
#define SHOP_VIEW_HPP

#include <vector>

class Product {
public:
    std::string name;
    double price;
    int quantity;

    Product(std::string n, double p, int q) : name(n), price(p), quantity(q) {}
};

class ShopView {
public:
    void displayProducts(const std::vector<Product> &products);
    void displayTotal(const std::vector<Product> &products);
};

#endif 