#include "Product.h"
#include "Cart.h"
#include <iomanip>

Product::Product() : id(0), name(""), description(""), price(0.0), stock(0), category("") {}

Product::Product(int id, const std::string& name, const std::string& description,
                 double price, int stock, const std::string& category)
    : id(id), name(name), description(description), price(price), stock(stock), category(category) {}

int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
std::string Product::getDescription() const { return description; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }
std::string Product::getCategory() const { return category; }

void Product::setName(const std::string& newName) { name = newName; }
void Product::setDescription(const std::string& newDesc) { description = newDesc; }
void Product::setPrice(double newPrice) { price = newPrice; }
void Product::setStock(int newStock) { stock = newStock; }

bool Product::operator==(const Product& other) const {
    return id == other.id;
}

bool Product::operator<(const Product& other) const {
    return price < other.price;
}

std::ostream& operator<<(std::ostream& os, const Product& product) {
    os << "[" << product.id << "] " << product.name 
       << " (" << product.category << ") - " 
       << std::fixed << std::setprecision(2) << product.price << " €";
    return os;
}

double applyDiscount(const Product& product, double percentage) {
    if (percentage < 0.0) percentage = 0.0;
    if (percentage > 100.0) percentage = 100.0;
    return product.price * (1.0 - percentage / 100.0);
}
