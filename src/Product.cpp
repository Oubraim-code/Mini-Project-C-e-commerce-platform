#include "../include/Product.hpp"
#include <iostream>

Product::Product(int id, std::string n, double p, int s) : id(id), name(n), price(p), stock(s) {}

int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }

bool Product::reduceStock(int q) {
    if (stock >= q) {
        stock -= q;
        return true;
    }
    return false;
}

void Product::display() const {
    std::cout << "[" << id << "] " << name << " - " << price << "€ (Stock: " << stock << ")" << std::endl;
}