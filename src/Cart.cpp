#include "Cart.h"
#include <iomanip>
#include <algorithm>

Cart::Cart() : discountRate(0.0) {}

void Cart::addItem(std::shared_ptr<Product> product, int quantity) {
    if (!product) {
        throw std::invalid_argument("Produit invalide");
    }
    if (quantity <= 0) {
        throw std::invalid_argument("La quantite doit etre positive");
    }
    if (quantity > product->getStock()) {
        throw std::runtime_error("Stock insuffisant. Disponible: " + 
                                  std::to_string(product->getStock()));
    }

    // Check if product already in cart
    for (auto& item : items) {
        if (item.product->getId() == product->getId()) {
            if (item.quantity + quantity > product->getStock()) {
                throw std::runtime_error("Stock insuffisant pour cette quantite");
            }
            item.quantity += quantity;
            return;
        }
    }

    items.emplace_back(product, quantity);
}

void Cart::removeItem(int productId) {
    auto it = std::remove_if(items.begin(), items.end(),
        [productId](const CartItem& item) {
            return item.product->getId() == productId;
        });

    if (it == items.end()) {
        throw std::runtime_error("Produit non trouve dans le panier");
    }

    items.erase(it, items.end());
}

void Cart::updateQuantity(int productId, int quantity) {
    if (quantity <= 0) {
        removeItem(productId);
        return;
    }

    for (auto& item : items) {
        if (item.product->getId() == productId) {
            if (quantity > item.product->getStock()) {
                throw std::runtime_error("Stock insuffisant");
            }
            item.quantity = quantity;
            return;
        }
    }

    throw std::runtime_error("Produit non trouve dans le panier");
}

void Cart::clear() {
    items.clear();
    discountRate = 0.0;
}

const std::vector<CartItem>& Cart::getItems() const {
    return items;
}

double Cart::getTotal() const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.product->getPrice() * item.quantity;
    }
    return total;
}

double Cart::getDiscountedTotal() const {
    return getTotal() * (1.0 - discountRate);
}

int Cart::getItemCount() const {
    int count = 0;
    for (const auto& item : items) {
        count += item.quantity;
    }
    return count;
}

double Cart::getDiscountRate() const {
    return discountRate;
}

void Cart::setDiscountRate(double rate) {
    if (rate < 0.0) rate = 0.0;
    if (rate > 1.0) rate = 1.0;
    discountRate = rate;
}

bool Cart::contains(int productId) const {
    for (const auto& item : items) {
        if (item.product->getId() == productId) {
            return true;
        }
    }
    return false;
}

Cart& Cart::operator+=(const CartItem& item) {
    addItem(item.product, item.quantity);
    return *this;
}

Cart& Cart::operator-=(int productId) {
    removeItem(productId);
    return *this;
}

const CartItem& Cart::operator[](size_t index) const {
    if (index >= items.size()) {
        throw std::out_of_range("Index hors limites");
    }
    return items[index];
}

void printCartSummary(const Cart& cart) {
    std::cout << "\n========== RESUME DU PANIER ==========" << std::endl;
    std::cout << "Nombre d'articles: " << cart.getItemCount() << std::endl;
    std::cout << "Sous-total: " << std::fixed << std::setprecision(2) 
              << cart.getTotal() << " €" << std::endl;
    if (cart.getDiscountRate() > 0) {
        std::cout << "Remise: " << cart.getDiscountRate() * 100 << "%" << std::endl;
        std::cout << "Total apres remise: " << cart.getDiscountedTotal() << " €" << std::endl;
    }
    std::cout << "======================================" << std::endl;
}

void Cart::display(std::ostream& os) const {
    if (items.empty()) {
        os << "Le panier est vide." << std::endl;
        return;
    }

    os << "\n========== CONTENU DU PANIER ==========" << std::endl;
    os << std::left << std::setw(5) << "Qte" 
       << std::setw(30) << "Produit" 
       << std::setw(15) << "Prix unit."
       << std::setw(15) << "Total" << std::endl;
    os << std::string(65, '-') << std::endl;

    for (const auto& item : items) {
        double lineTotal = item.product->getPrice() * item.quantity;
        os << std::left << std::setw(5) << item.quantity
           << std::setw(30) << item.product->getName()
           << std::setw(15) << std::fixed << std::setprecision(2) << item.product->getPrice() << " €"
           << std::setw(15) << lineTotal << " €" << std::endl;
    }

    os << std::string(65, '-') << std::endl;
    os << std::right << std::setw(50) << "Sous-total: " 
       << std::fixed << std::setprecision(2) << getTotal() << " €" << std::endl;

    if (discountRate > 0) {
        os << std::setw(50) << "Remise (" << discountRate * 100 << "%): -" 
           << getTotal() * discountRate << " €" << std::endl;
        os << std::setw(50) << "TOTAL: " << getDiscountedTotal() << " €" << std::endl;
    } else {
        os << std::setw(50) << "TOTAL: " << getTotal() << " €" << std::endl;
    }
    os << "=======================================" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Cart& cart) {
    cart.display(os);
    return os;
}
