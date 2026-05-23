#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <memory>
#include "Order.h"

// Forward declaration
class ECommercePlatform;

class Customer {
private:
    int id;
    std::string name;
    std::string email;
    std::string address;
    std::string phone;
    std::vector<std::shared_ptr<Order>> orderHistory;

public:
    // Constructors
    Customer();
    Customer(int id, const std::string& name, const std::string& email,
             const std::string& address, const std::string& phone);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getAddress() const;
    std::string getPhone() const;
    const std::vector<std::shared_ptr<Order>>& getOrderHistory() const;

    // Setters
    void setName(const std::string& newName);
    void setEmail(const std::string& newEmail);
    void setAddress(const std::string& newAddress);
    void setPhone(const std::string& newPhone);

    // Order management
    void addOrder(std::shared_ptr<Order> order);
    void displayOrderHistory() const;

    // Operator overloading
    bool operator==(const Customer& other) const;

    // Friend function for detailed display
    friend void displayCustomerDetails(const Customer& customer);

    // Friend class - platform can access private internals
    friend class ECommercePlatform;

    // Serialization
    std::string serialize() const;
    void deserialize(const std::vector<std::string>& data);
};

#endif // CUSTOMER_H
