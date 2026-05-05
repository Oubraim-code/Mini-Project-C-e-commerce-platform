#include <iostream>
#include <vector>
#include "include/Product.hpp"
#include "include/Customer.hpp"
#include "include/Cart.hpp"
#include "include/Order.hpp"
#include "include/Interface.hpp"

int main() {
    // 1. Initialize Data
    std::vector<Product*> inventory;
    inventory.push_back(new Product(1, "ThinkPad", 850.0, 5));
    inventory.push_back(new Product(2, "Logitech Mouse", 30.0, 10));
    inventory.push_back(new Product(3, "Mechanical Keyboard", 120.0, 0));

    Customer currentUser(101, "Brahim");
    Cart userCart;
    Interface ui;
    
    int choice = 0;
    while (choice != 4) {
        ui.displayCatalog(inventory);
        std::cout << "\n1. Add to Cart\n2. View Cart\n3. Checkout\n4. Exit\nSelection: ";
        std::cin >> choice;

        if (choice == 1) {
            ui.handleAddToCart(inventory, userCart);
        } 
        else if (choice == 2) {
            ui.clearScreen();
            ui.displayCart(userCart);
            std::cout << "\nPress Enter to return to catalog...";
            std::cin.ignore(); std::cin.get();
        }
        else if (choice == 3) {
            ui.clearScreen();
            Order finalOrder(7001, &currentUser, userCart.getItems());
            finalOrder.processOrder(0.20); // 20% TVA
            finalOrder.printReceipt();
            userCart.clearCart(); // Empty cart after buy
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(); std::cin.get();
        }
        ui.clearScreen();
    }

    // Cleanup memory
    for (auto p : inventory) delete p;
    
    return 0;
}