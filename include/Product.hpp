#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product {
private:
    int id;
    std::string name;
    double price;
    int stock;

public:
    Product(int id, std::string name, double price, int stock);
    
    // Getters
    int getId() const;
    std::string getName() const;
    double getPrice() const;
    int getStock() const;

    // Logic
    bool reduceStock(int quantity);
    void display() const;
};

#endif