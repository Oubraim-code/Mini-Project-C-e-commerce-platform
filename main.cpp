#include <iostream>
#include "include/Product.hpp"
#include "include/Customer.hpp"
#include "include/Cart.hpp"
#include "include/Order.hpp"

int main() {
    // 1. Setup Store (Inventory)
    Product laptop(1, "ThinkPad", 800.0, 5);
    Product mouse(2, "Logitech Mouse", 25.0, 10);

    // 2. Setup Customer
    Customer user1(101, "Brahim");

    // 3. Use the Cart
    Cart myCart;
    myCart.addItem(&laptop);
    myCart.addItem(&mouse);

    // 4. Create an Order from the Cart
    Order newOrder(5001, &user1, myCart.getItems());
    
    // 5. Process (Apply 20% TVA) and Print
    newOrder.processOrder(0.20);
    newOrder.printReceipt();

    return 0;
}