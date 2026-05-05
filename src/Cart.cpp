#include "../include/Cart.hpp"

void Cart::addItem(Product* p) { items.push_back(p); }
void Cart::clearCart() { items.clear(); }
std::vector<Product*> Cart::getItems() const { return items; }

double Cart::calculateSubtotal() const {
    double total = 0;
    for (auto p : items) total += p->getPrice();
    return total;
}