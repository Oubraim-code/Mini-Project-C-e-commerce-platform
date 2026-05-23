#include "Customer.h"
#include <iostream>
#include <iomanip>

Customer::Customer() : id(0), name(""), email(""), address(""), phone("") {}

Customer::Customer(int id, const std::string& name, const std::string& email,
                   const std::string& address, const std::string& phone)
    : id(id), name(name), email(email), address(address), phone(phone) {}

int Customer::getId() const { return id; }
std::string Customer::getName() const { return name; }
std::string Customer::getEmail() const { return email; }
std::string Customer::getAddress() const { return address; }
std::string Customer::getPhone() const { return phone; }
const std::vector<std::shared_ptr<Order>>& Customer::getOrderHistory() const { return orderHistory; }

void Customer::setName(const std::string& newName) { name = newName; }
void Customer::setEmail(const std::string& newEmail) { email = newEmail; }
void Customer::setAddress(const std::string& newAddress) { address = newAddress; }
void Customer::setPhone(const std::string& newPhone) { phone = newPhone; }

void Customer::addOrder(std::shared_ptr<Order> order) {
    if (order) {
        orderHistory.push_back(order);
    }
}

void Customer::displayOrderHistory() const {
    std::cout << "\n=== Historique des commandes de " << name << " ===" << std::endl;
    if (orderHistory.empty()) {
        std::cout << "Aucune commande." << std::endl;
        return;
    }

    double totalSpent = 0.0;
    for (const auto& order : orderHistory) {
        std::cout << *order << std::endl;
        totalSpent += order->getTotal();
    }
    std::cout << "Total depense: " << std::fixed << std::setprecision(2) 
              << totalSpent << " €" << std::endl;
}

bool Customer::operator==(const Customer& other) const {
    return id == other.id;
}

void displayCustomerDetails(const Customer& customer) {
    std::cout << "\n=== Details Client ===" << std::endl;
    std::cout << "ID: " << customer.id << std::endl;
    std::cout << "Nom: " << customer.name << std::endl;
    std::cout << "Email: " << customer.email << std::endl;
    std::cout << "Adresse: " << customer.address << std::endl;
    std::cout << "Telephone: " << customer.phone << std::endl;
    std::cout << "Commandes: " << customer.orderHistory.size() << std::endl;
    std::cout << "======================" << std::endl;
}

std::string Customer::serialize() const {
    return "CUSTOMER|" + std::to_string(id) + "|" + name + "|" + email + "|" + address + "|" + phone;
}

void Customer::deserialize(const std::vector<std::string>& data) {
    if (data.size() >= 6) {
        id = std::stoi(data[1]);
        name = data[2];
        email = data[3];
        address = data[4];
        phone = data[5];
    }
}
