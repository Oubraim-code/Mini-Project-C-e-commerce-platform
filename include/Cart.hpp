#ifndef CART_HPP
#define CART_HPP

#include <vector>
#include "Product.hpp"

class Cart {
private:
    std::vector<Product*> items; // Pointers to products in the store

public:
    void addItem(Product* p);
    void clearCart();
    std::vector<Product*> getItems() const;
    double calculateSubtotal() const;
};

#endif