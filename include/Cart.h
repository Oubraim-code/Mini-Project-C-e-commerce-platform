#ifndef CART_H
#define CART_H

#include <vector>
#include <memory>
#include <stdexcept>
#include "Product.h"

struct CartItem {
    std::shared_ptr<Product> product;
    int quantity;

    CartItem(std::shared_ptr<Product> p, int q) : product(p), quantity(q) {}
};

class Cart {
private:
    std::vector<CartItem> items;
    double discountRate; // 0.0 to 1.0

public:
    Cart();

    // Core operations
    void addItem(std::shared_ptr<Product> product, int quantity);
    void removeItem(int productId);
    void updateQuantity(int productId, int quantity);
    void clear();

    // Getters
    const std::vector<CartItem>& getItems() const;
    double getTotal() const;
    double getDiscountedTotal() const;
    int getItemCount() const;
    double getDiscountRate() const;

    // Discount management
    void setDiscountRate(double rate);

    // Check if product is in cart
    bool contains(int productId) const;

    // Operator overloading
    Cart& operator+=(const CartItem& item);
    Cart& operator-=(int productId);
    const CartItem& operator[](size_t index) const;

    // Friend function for cart summary
    friend void printCartSummary(const Cart& cart);

    // Display
    void display(std::ostream& os) const;
};

std::ostream& operator<<(std::ostream& os, const Cart& cart);

#endif // CART_H
