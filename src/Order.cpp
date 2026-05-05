#include "../include/Order.hpp"
#include <iostream>

Order::Order(int id, Customer* c, std::vector<Product*> items) 
    : orderId(id), customer(c), orderedItems(items), totalAmount(0) {}

void Order::processOrder(double tva) {
    double subtotal = 0;
    for (auto p : orderedItems) {
        if (p->reduceStock(1)) { // Try to take 1 from stock
            subtotal += p->getPrice();
        }
    }
    totalAmount = subtotal * (1 + tva);
}

void Order::printReceipt() const {
    std::cout << "\n--- RECEIPT (Order #" << orderId << ") ---" << std::endl;
    std::cout << "Customer: " << customer->getName() << std::endl;
    for (auto p : orderedItems) {
        std::cout << "- " << p->getName() << " : " << p->getPrice() << "€" << std::endl;
    }
    std::cout << "Total (inc. TVA): " << totalAmount << "€" << std::endl;
}