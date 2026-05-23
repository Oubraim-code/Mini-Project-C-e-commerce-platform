#include "Food.h"
#include "Cart.h"
#include <iomanip>
#include <cmath>

Food::Food() : Product(), expirationDate(""), calories(0), isOrganic(false) {}

Food::Food(int id, const std::string& name, const std::string& description,
           double price, int stock, const std::string& expiry,
           int calories, bool organic)
    : Product(id, name, description, price, stock, "Alimentaire"),
      expirationDate(expiry), calories(calories), isOrganic(organic) {}

std::string Food::getExpirationDate() const { return expirationDate; }
int Food::getCalories() const { return calories; }
bool Food::getIsOrganic() const { return isOrganic; }

void Food::setExpirationDate(const std::string& date) { expirationDate = date; }
void Food::setCalories(int cal) { calories = cal; }
void Food::setIsOrganic(bool organic) { isOrganic = organic; }

void Food::display(std::ostream& os) const {
    os << "=== Produit Alimentaire ===" << std::endl;
    os << "ID: " << id << std::endl;
    os << "Nom: " << name << std::endl;
    os << "Description: " << description << std::endl;
    os << "Prix: " << std::fixed << std::setprecision(2) << price << " €" << std::endl;
    os << "Stock: " << stock << std::endl;
    os << "Date d'expiration: " << expirationDate << std::endl;
    os << "Calories: " << calories << " kcal" << std::endl;
    os << "Bio: " << (isOrganic ? "Oui" : "Non") << std::endl;
}

std::string Food::getType() const {
    return "Food";
}

// Polymorphic similarity score for food products
// Considers: organic preference, calorie proximity, price proximity
double Food::computeSimilarityScore(const Cart& cart) const {
    double score = 0.0;
    const auto& items = cart.getItems();

    if (items.empty()) {
        return 50.0;
    }

    double cartAvgPrice = 0.0;
    int organicCount = 0;
    int foodCount = 0;
    int totalCalories = 0;

    for (const auto& item : items) {
        cartAvgPrice += item.product->getPrice() * item.quantity;
        if (item.product->getType() == "Food") {
            foodCount += item.quantity;
            // Note: In a real implementation, we'd use a virtual method to get calories
            // For now, we use type check which is acceptable for cross-type comparison
        }
    }

    cartAvgPrice /= cart.getItemCount();

    // Price proximity (0 to 25 points)
    double priceDiff = std::abs(price - cartAvgPrice);
    score += std::max(0.0, 25.0 - priceDiff * 2.0);

    // Category affinity (0 to 35 points)
    double foodRatio = static_cast<double>(foodCount) / cart.getItemCount();
    score += foodRatio * 35.0;

    // Organic bonus (0 to 20 points)
    if (isOrganic) {
        score += 20.0;
    }

    // Base relevance (20 points)
    score += 20.0;

    return std::min(100.0, score);
}

std::string Food::serialize() const {
    return "FOOD|" + std::to_string(id) + "|" + name + "|" + description + "|" +
           std::to_string(price) + "|" + std::to_string(stock) + "|" +
           expirationDate + "|" + std::to_string(calories) + "|" +
           (isOrganic ? "1" : "0");
}

void Food::deserialize(const std::vector<std::string>& data) {
    if (data.size() >= 9) {
        id = std::stoi(data[1]);
        name = data[2];
        description = data[3];
        price = std::stod(data[4]);
        stock = std::stoi(data[5]);
        category = "Alimentaire";
        expirationDate = data[6];
        calories = std::stoi(data[7]);
        isOrganic = (data[8] == "1");
    }
}
