#include "Interface.hpp"
#include <iostream>
#include <iomanip>

// Colors for Linux terminal
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"

void Interface::clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // Standard POSIX clear screen
}

void Interface::printHeader(std::string title) {
    std::cout << CYAN << "========================================" << RESET << std::endl;
    std::cout << YELLOW << "    " << title << RESET << std::endl;
    std::cout << CYAN << "========================================" << RESET << std::endl;
}

void Interface::displayCatalog(const std::vector<Product*>& products) {
    printHeader("MINI-AMAZON CATALOG");
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "NAME" 
              << std::setw(10) << "PRICE" 
              << "STOCK" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    for (const auto& p : products) {
        std::cout << std::left << std::setw(5) << p->getId() 
                  << std::setw(20) << p->getName() 
                  << std::setw(10) << (std::to_string(p->getPrice()) + "€");
        
        if (p->getStock() > 0) {
            std::cout << GREEN << p->getStock() << RESET << std::endl;
        } else {
            std::cout << RED << "OUT OF STOCK" << RESET << std::endl;
        }
    }
}

void Interface::displayCart(const Cart& cart) {
    printHeader("YOUR SHOPPING CART");
    auto items = cart.getItems();
    if (items.empty()) {
        std::cout << "Your cart is empty." << std::endl;
        return;
    }

    for (auto p : items) {
        std::cout << "- " << p->getName() << " : " << p->getPrice() << "€" << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    std::cout << GREEN << "Subtotal: " << cart.calculateSubtotal() << "€" << RESET << std::endl;
}

void Interface::handleAddToCart(std::vector<Product*>& inventory, Cart& cart) {
    int id;
    std::cout << "\nEnter Product ID to add: ";
    std::cin >> id;

    bool found = false;
    for (auto p : inventory) {
        if (p->getId() == id) {
            if (p->getStock() > 0) {
                cart.addItem(p);
                std::cout << GREEN << "[+] Added " << p->getName() << " to cart!" << RESET << std::endl;
            } else {
                std::cout << RED << "[!] Item out of stock." << RESET << std::endl;
            }
            found = true;
            break;
        }
    }
    if (!found) std::cout << RED << "[!] Product ID not found." << RESET << std::endl;
}