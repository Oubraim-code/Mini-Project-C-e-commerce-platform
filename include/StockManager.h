#ifndef STOCKMANAGER_H
#define STOCKMANAGER_H

#include <vector>
#include <memory>
#include <map>
#include <string>
#include <iostream>
#include "Product.h"

class StockManager {
private:
    std::vector<std::shared_ptr<Product>> products;
    std::map<int, int> stockLevels; // productId -> stock
    int lowStockThreshold;
    static int nextProductId;

    // Private constructor for singleton-like behavior (but we'll use regular instance)
    StockManager();

public:
    // Get singleton instance
    static StockManager& getInstance();

    // Prevent copy
    StockManager(const StockManager&) = delete;
    StockManager& operator=(const StockManager&) = delete;

    // Product management
    void addProduct(std::shared_ptr<Product> product);
    void removeProduct(int productId);
    std::shared_ptr<Product> findProduct(int productId) const;
    std::shared_ptr<Product> findProductByName(const std::string& name) const;

    // Stock operations
    bool updateStock(int productId, int quantity);
    bool reserveStock(int productId, int quantity);
    bool releaseStock(int productId, int quantity);
    int getStock(int productId) const;

    // Queries
    std::vector<std::shared_ptr<Product>> getAllProducts() const;
    std::vector<std::shared_ptr<Product>> getProductsByCategory(const std::string& category) const;
    std::vector<std::shared_ptr<Product>> getLowStockProducts() const;

    // Alerts
    void checkLowStock() const;
    void setLowStockThreshold(int threshold);

    // Persistence
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    // Display
    void displayInventory(std::ostream& os) const;

    // Get next ID
    int getNextId();

    // Friend function for inventory report
    friend void generateInventoryReport(const StockManager& manager);
};

#endif // STOCKMANAGER_H
