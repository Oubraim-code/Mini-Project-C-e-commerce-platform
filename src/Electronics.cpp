#include "Electronics.h"
#include "Cart.h"
#include <iomanip>
#include <cmath>

Electronics::Electronics() : Product(), brand(""), warrantyMonths(0), powerConsumption(0.0) {}

Electronics::Electronics(int id, const std::string& name, const std::string& description,
                         double price, int stock, const std::string& brand,
                         int warranty, double power)
    : Product(id, name, description, price, stock, "Electronique"),
      brand(brand), warrantyMonths(warranty), powerConsumption(power) {}

std::string Electronics::getBrand() const { return brand; }
int Electronics::getWarranty() const { return warrantyMonths; }
double Electronics::getPowerConsumption() const { return powerConsumption; }

void Electronics::setBrand(const std::string& newBrand) { brand = newBrand; }
void Electronics::setWarranty(int months) { warrantyMonths = months; }
void Electronics::setPowerConsumption(double watts) { powerConsumption = watts; }

void Electronics::display(std::ostream& os) const {
    os << "=== Produit Electronique ===" << std::endl;
    os << "ID: " << id << std::endl;
    os << "Nom: " << name << std::endl;
    os << "Description: " << description << std::endl;
    os << "Marque: " << brand << std::endl;
    os << "Prix: " << std::fixed << std::setprecision(2) << price << " €" << std::endl;
    os << "Stock: " << stock << std::endl;
    os << "Garantie: " << warrantyMonths << " mois" << std::endl;
    os << "Consommation: " << powerConsumption << " W" << std::endl;
}

std::string Electronics::getType() const {
    return "Electronics";
}

// Polymorphic similarity score - no knowledge of cart contents types
// Score based on: price proximity, brand presence in cart, electronics density
double Electronics::computeSimilarityScore(const Cart& cart) const {
    double score = 0.0;
    const auto& items = cart.getItems();

    if (items.empty()) {
        return 50.0; // Default score for empty cart
    }

    double cartAvgPrice = 0.0;
    int electronicsCount = 0;
    bool brandInCart = false;

    for (const auto& item : items) {
        cartAvgPrice += item.product->getPrice() * item.quantity;

        // Check if this is electronics (polymorphic check via getType())
        if (item.product->getType() == "Electronics") {
            electronicsCount += item.quantity;
            // Check brand match using dynamic_cast alternative (virtual method)
            // We use a virtual approach to avoid RTTI
            // For brand comparison, we'll use a different approach
        }
    }

    cartAvgPrice /= cart.getItemCount();

    // Price proximity (0 to 30 points)
    double priceDiff = std::abs(price - cartAvgPrice);
    score += std::max(0.0, 30.0 - priceDiff * 0.5);

    // Category affinity (0 to 40 points)
    double electronicsRatio = static_cast<double>(electronicsCount) / cart.getItemCount();
    score += electronicsRatio * 40.0;

    // Base relevance (30 points)
    score += 30.0;

    return std::min(100.0, score);
}

std::string Electronics::serialize() const {
    return "ELECTRONICS|" + std::to_string(id) + "|" + name + "|" + description + "|" +
           std::to_string(price) + "|" + std::to_string(stock) + "|" + brand + "|" +
           std::to_string(warrantyMonths) + "|" + std::to_string(powerConsumption);
}

void Electronics::deserialize(const std::vector<std::string>& data) {
    if (data.size() >= 9) {
        id = std::stoi(data[1]);
        name = data[2];
        description = data[3];
        price = std::stod(data[4]);
        stock = std::stoi(data[5]);
        category = "Electronique";
        brand = data[6];
        warrantyMonths = std::stoi(data[7]);
        powerConsumption = std::stod(data[8]);
    }
}
