#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "Cart.h"

enum class OrderStatus {
    PENDING,
    PROCESSING,
    SHIPPED,
    DELIVERED,
    CANCELLED
};

class Order {
private:
    int id;
    int customerId;
    std::vector<CartItem> items;
    double subtotal;
    double tax;
    double discount;
    double total;
    OrderStatus status;
    std::string orderDate;
    std::string deliveryDate;

public:
    // Constructors
    Order();
    Order(int id, int customerId, const std::vector<CartItem>& items,
          double subtotal, double tax, double discount, double total);

    // Getters
    int getId() const;
    int getCustomerId() const;
    double getTotal() const;
    OrderStatus getStatus() const;
    std::string getOrderDate() const;
    std::string getDeliveryDate() const;
    const std::vector<CartItem>& getItems() const;

    // Setters
    void setStatus(OrderStatus newStatus);
    void setDeliveryDate(const std::string& date);

    // Status management
    void advanceStatus();
    std::string statusToString() const;

    // Operator overloading
    bool operator<(const Order& other) const;

    // Friend function for order receipt
    friend void generateOrderReceipt(const Order& order);

    // Serialization
    std::string serialize() const;
    void deserialize(const std::vector<std::string>& data);

    // Display
    void display(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const Order& order);
std::ostream& operator<<(std::ostream& os, OrderStatus status);

#endif // ORDER_H
