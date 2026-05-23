#include "StockManager.h"
#include "Electronics.h"
#include "Food.h"
#include "Clothing.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

int StockManager::nextProductId = 100;

StockManager::StockManager() : lowStockThreshold(5) {}

StockManager& StockManager::getInstance() {
    static StockManager instance;
    return instance;
}

void StockManager::addProduct(std::shared_ptr<Product> product) {
    if (product) {
        products.push_back(product);
        stockLevels[product->getId()] = product->getStock();
    }
}

void StockManager::removeProduct(int productId) {
    auto it = std::remove_if(products.begin(), products.end(),
        [productId](const std::shared_ptr<Product>& p) {
            return p->getId() == productId;
        });
    products.erase(it, products.end());
    stockLevels.erase(productId);
}

std::shared_ptr<Product> StockManager::findProduct(int productId) const {
    for (const auto& product : products) {
        if (product->getId() == productId) {
            return product;
        }
    }
    return nullptr;
}

std::shared_ptr<Product> StockManager::findProductByName(const std::string& name) const {
    for (const auto& product : products) {
        if (product->getName() == name) {
            return product;
        }
    }
    return nullptr;
}

bool StockManager::updateStock(int productId, int quantity) {
    auto product = findProduct(productId);
    if (!product) return false;

    int newStock = product->getStock() + quantity;
    if (newStock < 0) return false;

    product->setStock(newStock);
    stockLevels[productId] = newStock;
    return true;
}

bool StockManager::reserveStock(int productId, int quantity) {
    auto product = findProduct(productId);
    if (!product || product->getStock() < quantity) return false;

    product->setStock(product->getStock() - quantity);
    stockLevels[productId] = product->getStock();
    return true;
}

bool StockManager::releaseStock(int productId, int quantity) {
    return updateStock(productId, quantity);
}

int StockManager::getStock(int productId) const {
    auto it = stockLevels.find(productId);
    return (it != stockLevels.end()) ? it->second : -1;
}

std::vector<std::shared_ptr<Product>> StockManager::getAllProducts() const {
    return products;
}

std::vector<std::shared_ptr<Product>> StockManager::getProductsByCategory(const std::string& category) const {
    std::vector<std::shared_ptr<Product>> result;
    for (const auto& product : products) {
        if (product->getCategory() == category) {
            result.push_back(product);
        }
    }
    return result;
}

std::vector<std::shared_ptr<Product>> StockManager::getLowStockProducts() const {
    std::vector<std::shared_ptr<Product>> result;
    for (const auto& product : products) {
        if (product->getStock() <= lowStockThreshold) {
            result.push_back(product);
        }
    }
    return result;
}

void StockManager::checkLowStock() const {
    auto lowStock = getLowStockProducts();
    if (!lowStock.empty()) {
        std::cout << "\n⚠️  ALERTES STOCK FAIBLE:" << std::endl;
        for (const auto& product : lowStock) {
            std::cout << "  - " << product->getName() 
                      << " (Stock: " << product->getStock() << ")" << std::endl;
        }
    }
}

void StockManager::setLowStockThreshold(int threshold) {
    if (threshold > 0) {
        lowStockThreshold = threshold;
    }
}

bool StockManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto& product : products) {
        file << product->serialize() << std::endl;
    }

    file.close();
    return true;
}

bool StockManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    products.clear();
    stockLevels.clear();

    std::string line;
    while (std::getline(file, line)) {
        auto parts = Utils::split(line, '|');
        if (parts.empty()) continue;

        std::shared_ptr<Product> product;
        if (parts[0] == "ELECTRONICS") {
            product = std::make_shared<Electronics>();
        } else if (parts[0] == "FOOD") {
            product = std::make_shared<Food>();
        } else if (parts[0] == "CLOTHING") {
            product = std::make_shared<Clothing>();
        }

        if (product) {
            product->deserialize(parts);
            products.push_back(product);
            stockLevels[product->getId()] = product->getStock();
        }
    }

    file.close();
    return true;
}

void StockManager::displayInventory(std::ostream& os) const {
    os << "\n========== CATALOGUE PRODUITS ==========" << std::endl;
    os << std::left << std::setw(5) << "ID" 
       << std::setw(25) << "Nom" 
       << std::setw(15) << "Categorie"
       << std::setw(12) << "Prix"
       << std::setw(10) << "Stock" << std::endl;
    os << std::string(67, '-') << std::endl;

    for (const auto& product : products) {
        os << std::left << std::setw(5) << product->getId()
           << std::setw(25) << product->getName()
           << std::setw(15) << product->getCategory()
           << std::setw(12) << std::fixed << std::setprecision(2) << product->getPrice() << " €"
           << std::setw(10) << product->getStock() << std::endl;
    }
    os << "=======================================" << std::endl;
}

int StockManager::getNextId() {
    return nextProductId++;
}

void generateInventoryReport(const StockManager& manager) {
    auto products = manager.getAllProducts();
    int totalProducts = products.size();
    int totalStock = 0;
    double totalValue = 0.0;
    int lowStockCount = manager.getLowStockProducts().size();

    for (const auto& p : products) {
        totalStock += p->getStock();
        totalValue += p->getPrice() * p->getStock();
    }

    std::cout << "\n========== RAPPORT INVENTAIRE ==========" << std::endl;
    std::cout << "Total produits: " << totalProducts << std::endl;
    std::cout << "Total unites en stock: " << totalStock << std::endl;
    std::cout << "Valeur totale: " << std::fixed << std::setprecision(2) << totalValue << " €" << std::endl;
    std::cout << "Produits en stock faible: " << lowStockCount << std::endl;
    std::cout << "=========================================" << std::endl;
}
