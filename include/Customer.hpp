#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include <vector>

class Customer {
private:
    int id;
    std::string name;

public:
    Customer(int id, std::string name);
    std::string getName() const;
    int getId() const;
};

#endif