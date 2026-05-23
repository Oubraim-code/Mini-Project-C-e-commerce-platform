#ifndef ECOMMERCEPLATFORM_H
#define ECOMMERCEPLATFORM_H

#include <memory>
#include <vector>
#include <map>
#include "StockManager.h"
#include "Customer.h"
#include "Cart.h"
#include "Order.h"
#include "RecommendationEngine.h"

class ECommercePlatform {
private:
    StockManager& stockManager;
    std::vector<std::shared_ptr<Customer>> customers;
    std::vector<std::shared_ptr<Order>> orders;
    std::map<int, Cart> customerCarts; // Cart by value, not shared_ptr
    RecommendationEngine recommendationEngine;
    static int nextCustomerId;
    static int nextOrderId;

    // Menu handlers
    void showMainMenu();
    void handleProductManagement();
    void handleCustomerManagement();
    void handleShopping();
    void handleOrders();
    void handleRecommendations();

    // Helper methods
    void displayCatalog() const;
    std::shared_ptr<Customer> findCustomer(int id) const;
    std::shared_ptr<Order> findOrder(int id) const;
    void initializeDemoData();

    // Friend function for platform analytics
    friend void displayPlatformStats(const ECommercePlatform& platform);

public:
    ECommercePlatform();

    // Core lifecycle
    void initialize();
    void run();
    void shutdown();

    // Customer operations
    void registerCustomer();
    void listCustomers() const;

    // Shopping operations
    void addToCart(int customerId);
    void viewCart(int customerId);
    void checkout(int customerId);

    // Order operations
    void viewOrders(int customerId) const;
    void updateOrderStatus();

    // Recommendations
    void showRecommendations(int customerId);

    // Persistence
    void saveData();
    void loadData();
};

#endif // ECOMMERCEPLATFORM_H
