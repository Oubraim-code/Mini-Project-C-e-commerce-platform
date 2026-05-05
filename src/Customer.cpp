#include "../include/Customer.hpp"

Customer::Customer(int id, std::string n) : id(id), name(n) {}
std::string Customer::getName() const { return name; }
int Customer::getId() const { return id; }