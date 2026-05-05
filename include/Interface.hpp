#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <vector>
#include "Product.hpp"
#include "Cart.hpp"
#include "Customer.hpp"

class Interface {
public:
    // UI Helpers
    void clearScreen();
    void printHeader(std::string title);
    
    // Main Views
    void displayCatalog(const std::vector<Product*>& products);
    void displayCart(const Cart& cart);
    
    // Logic Handlers
    void handleAddToCart(std::vector<Product*>& inventory, Cart& cart);
};

#endif