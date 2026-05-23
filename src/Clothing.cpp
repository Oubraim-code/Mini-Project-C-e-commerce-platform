#include "Clothing.h"
#include "Cart.h"
#include <iomanip>
#include <cmath>

Clothing::Clothing() : Product(), size(""), color(""), material("") {}

Clothing::Clothing(int id, const std::string& name, const std::string& description,
                   double price, int stock, const std::string& size,
                   const std::string& color, const std::string& material)
    : Product(id, name, description, price, stock, "Vetement"),
      size(size), color(color), material(material) {}

std::string Clothing::getSize() const { return size; }
std::string Clothing::getColor() const { return color; }
std::string Clothing::getMaterial() const { return material; }

void Clothing::setSize(const std::string& newSize) { size = newSize; }
void Clothing::setColor(const std::string& newColor) { color = newColor; }
void Clothing::setMaterial(const std::string& newMaterial) { material = newMaterial; }

void Clothing::display(std::ostream& os) const {
    os << "=== Produit Vetement ===" << std::endl;
    os << "ID: " << id << std::endl;
    os << "Nom: " << name << std::endl;
    os << "Description: " << description << std::endl;
    os << "Prix: " << std::fixed << std::setprecision(2) << price << " €" << std::endl;
    os << "Stock: " << stock << std::endl;
    os << "Taille: " << size << std::endl;
    os << "Couleur: " << color << std::endl;
    os << "Matiere: " << material << std::endl;
}

std::string Clothing::getType() const {
    return "Clothing";
}

// Polymorphic similarity score for clothing
// Considers: price proximity, clothing density in cart, material diversity
double Clothing::computeSimilarityScore(const Cart& cart) const {
    double score = 0.0;
    const auto& items = cart.getItems();

    if (items.empty()) {
        return 50.0;
    }

    double cartAvgPrice = 0.0;
    int clothingCount = 0;

    for (const auto& item : items) {
        cartAvgPrice += item.product->getPrice() * item.quantity;
        if (item.product->getType() == "Clothing") {
            clothingCount += item.quantity;
        }
    }

    cartAvgPrice /= cart.getItemCount();

    // Price proximity (0 to 30 points)
    double priceDiff = std::abs(price - cartAvgPrice);
    score += std::max(0.0, 30.0 - priceDiff * 1.5);

    // Category affinity (0 to 45 points)
    double clothingRatio = static_cast<double>(clothingCount) / cart.getItemCount();
    score += clothingRatio * 45.0;

    // Material diversity bonus (0 to 15 points)
    // Simplified: assume cotton and linen are popular
    if (material == "Coton" || material == "Linen") {
        score += 15.0;
    } else {
        score += 5.0;
    }

    // Base relevance (10 points)
    score += 10.0;

    return std::min(100.0, score);
}

std::string Clothing::serialize() const {
    return "CLOTHING|" + std::to_string(id) + "|" + name + "|" + description + "|" +
           std::to_string(price) + "|" + std::to_string(stock) + "|" +
           size + "|" + color + "|" + material;
}

void Clothing::deserialize(const std::vector<std::string>& data) {
    if (data.size() >= 9) {
        id = std::stoi(data[1]);
        name = data[2];
        description = data[3];
        price = std::stod(data[4]);
        stock = std::stoi(data[5]);
        category = "Vetement";
        size = data[6];
        color = data[7];
        material = data[8];
    }
}
