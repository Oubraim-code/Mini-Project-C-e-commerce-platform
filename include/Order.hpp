#ifndef ORDER_HPP
#define ORDER_HPP

#include "Customer.hpp"
#include "Product.hpp"
#include <vector>

class Order {
private:
    int orderId;
    Customer* customer;
    std::vector<Product*> orderedItems;
    double totalAmount;

public:
    Order(int id, Customer* c, std::vector<Product*> items);
    void processOrder(double tva);
    void printReceipt() const;
};

#endif