#include "ECommercePlatform.h"
#include "Utils.h"
#include "Electronics.h"
#include "Food.h"
#include "Clothing.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>

int ECommercePlatform::nextCustomerId = 1;
int ECommercePlatform::nextOrderId = 1000;

ECommercePlatform::ECommercePlatform() : stockManager(StockManager::getInstance()) {}

void ECommercePlatform::initialize() {
    std::cout << "\n╔══════════════════════════════════════╗" << std::endl;
    std::cout << "║     MINI-AMAZON E-COMMERCE           ║" << std::endl;
    std::cout << "║     Plateforme de vente en ligne     ║" << std::endl;
    std::cout << "╚══════════════════════════════════════╝" << std::endl;

    // Try to load existing data
    if (!stockManager.loadFromFile("data/products.dat")) {
        std::cout << "\n[INFO] Initialisation avec donnees de demonstration..." << std::endl;
        initializeDemoData();
    }

    stockManager.checkLowStock();
}

void ECommercePlatform::run() {
    bool running = true;
    while (running) {
        showMainMenu();
        int choice = Utils::readInt("Votre choix: ", 0, 6);

        switch (choice) {
            case 1: handleProductManagement(); break;
            case 2: handleCustomerManagement(); break;
            case 3: handleShopping(); break;
            case 4: handleOrders(); break;
            case 5: handleRecommendations(); break;
            case 6: 
                saveData();
                std::cout << "\nDonnees sauvegardees. Au revoir!" << std::endl;
                running = false;
                break;
            case 0: running = false; break;
        }
    }
}

void ECommercePlatform::shutdown() {
    saveData();
    std::cout << "\nPlateforme arretee proprement." << std::endl;
}

void ECommercePlatform::showMainMenu() {
    std::cout << "\n========== MENU PRINCIPAL ==========" << std::endl;
    std::cout << "1. Gestion des produits" << std::endl;
    std::cout << "2. Gestion des clients" << std::endl;
    std::cout << "3. Shopping (Panier)" << std::endl;
    std::cout << "4. Gestion des commandes" << std::endl;
    std::cout << "5. Recommandations" << std::endl;
    std::cout << "6. Sauvegarder et quitter" << std::endl;
    std::cout << "0. Quitter sans sauvegarder" << std::endl;
    std::cout << "====================================" << std::endl;
}

void ECommercePlatform::handleProductManagement() {
    std::cout << "\n--- Gestion des Produits ---" << std::endl;
    std::cout << "1. Voir le catalogue" << std::endl;
    std::cout << "2. Ajouter un produit" << std::endl;
    std::cout << "3. Rechercher un produit" << std::endl;
    std::cout << "4. Alertes stock" << std::endl;
    std::cout << "5. Rapport inventaire" << std::endl;
    std::cout << "0. Retour" << std::endl;

    int choice = Utils::readInt("Choix: ", 0, 5);

    switch (choice) {
        case 1:
            stockManager.displayInventory(std::cout);
            break;
        case 2: {
            std::cout << "\nTypes: 1=Electronique, 2=Alimentaire, 3=Vetement" << std::endl;
            int type = Utils::readInt("Type: ", 1, 3);

            int id = stockManager.getNextId();
            std::string name = Utils::readString("Nom: ");
            std::string desc = Utils::readString("Description: ");
            double price = Utils::readDouble("Prix (€): ", 0.01, 10000.0);
            int stock = Utils::readInt("Stock initial: ", 0, 10000);

            std::shared_ptr<Product> product;
            if (type == 1) {
                std::string brand = Utils::readString("Marque: ");
                int warranty = Utils::readInt("Garantie (mois): ", 0, 120);
                double power = Utils::readDouble("Consommation (W): ", 0.0, 5000.0);
                product = std::make_shared<Electronics>(id, name, desc, price, stock, brand, warranty, power);
            } else if (type == 2) {
                std::string expiry = Utils::readString("Date expiration (YYYY-MM-DD): ");
                int calories = Utils::readInt("Calories: ", 0, 10000);
                std::cout << "Bio? (1=Oui, 0=Non): ";
                int organic; std::cin >> organic;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                product = std::make_shared<Food>(id, name, desc, price, stock, expiry, calories, organic == 1);
            } else {
                std::string size = Utils::readString("Taille: ");
                std::string color = Utils::readString("Couleur: ");
                std::string material = Utils::readString("Matiere: ");
                product = std::make_shared<Clothing>(id, name, desc, price, stock, size, color, material);
            }

            stockManager.addProduct(product);
            std::cout << "\n✅ Produit ajoute avec ID: " << id << std::endl;
            break;
        }
        case 3: {
            std::string name = Utils::readString("Nom du produit: ");
            auto product = stockManager.findProductByName(name);
            if (product) {
                product->display(std::cout);
            } else {
                std::cout << "Produit non trouve." << std::endl;
            }
            break;
        }
        case 4:
            stockManager.checkLowStock();
            break;
        case 5:
            generateInventoryReport(stockManager);
            break;
    }
}

void ECommercePlatform::handleCustomerManagement() {
    std::cout << "\n--- Gestion des Clients ---" << std::endl;
    std::cout << "1. Inscrire un client" << std::endl;
    std::cout << "2. Liste des clients" << std::endl;
    std::cout << "3. Details client" << std::endl;
    std::cout << "0. Retour" << std::endl;

    int choice = Utils::readInt("Choix: ", 0, 3);

    switch (choice) {
        case 1:
            registerCustomer();
            break;
        case 2:
            listCustomers();
            break;
        case 3: {
            int id = Utils::readInt("ID client: ", 1, 9999);
            auto customer = findCustomer(id);
            if (customer) {
                displayCustomerDetails(*customer);
            } else {
                std::cout << "Client non trouve." << std::endl;
            }
            break;
        }
    }
}

void ECommercePlatform::registerCustomer() {
    int id = nextCustomerId++;
    std::string name = Utils::readString("Nom: ");
    std::string email = Utils::readString("Email: ");
    std::string address = Utils::readString("Adresse: ");
    std::string phone = Utils::readString("Telephone: ");

    auto customer = std::make_shared<Customer>(id, name, email, address, phone);
    customers.push_back(customer);
    customerCarts[id] = Cart();

    std::cout << "\n✅ Client inscrit avec ID: " << id << std::endl;
}

void ECommercePlatform::listCustomers() const {
    std::cout << "\n========== LISTE CLIENTS ==========" << std::endl;
    if (customers.empty()) {
        std::cout << "Aucun client inscrit." << std::endl;
        return;
    }

    for (const auto& customer : customers) {
        std::cout << "[" << customer->getId() << "] " << customer->getName() 
                  << " - " << customer->getEmail() << std::endl;
    }
}

void ECommercePlatform::handleShopping() {
    if (customers.empty()) {
        std::cout << "\nAucun client inscrit. Veuillez d'abord inscrire un client." << std::endl;
        return;
    }

    listCustomers();
    int customerId = Utils::readInt("ID client: ", 1, 9999);
    auto customer = findCustomer(customerId);
    if (!customer) {
        std::cout << "Client non trouve." << std::endl;
        return;
    }

    Cart& cart = customerCarts[customerId];

    bool shopping = true;
    while (shopping) {
        std::cout << "\n--- Shopping (" << customer->getName() << ") ---" << std::endl;
        std::cout << "1. Voir le catalogue" << std::endl;
        std::cout << "2. Ajouter au panier" << std::endl;
        std::cout << "3. Voir le panier" << std::endl;
        std::cout << "4. Modifier quantite" << std::endl;
        std::cout << "5. Retirer du panier" << std::endl;
        std::cout << "6. Appliquer remise" << std::endl;
        std::cout << "7. Passer commande" << std::endl;
        std::cout << "0. Retour" << std::endl;

        int choice = Utils::readInt("Choix: ", 0, 7);

        switch (choice) {
            case 1:
                stockManager.displayInventory(std::cout);
                break;
            case 2:
                addToCart(customerId);
                break;
            case 3:
                viewCart(customerId);
                break;
            case 4: {
                int pid = Utils::readInt("ID produit: ", 1, 9999);
                int qty = Utils::readInt("Nouvelle quantite: ", 0, 1000);
                try {
                    cart.updateQuantity(pid, qty);
                    std::cout << "Quantite mise a jour." << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Erreur: " << e.what() << std::endl;
                }
                break;
            }
            case 5: {
                int pid = Utils::readInt("ID produit a retirer: ", 1, 9999);
                try {
                    cart -= pid;
                    std::cout << "Produit retire." << std::endl;
                } catch (const std::exception& e) {
                    std::cout << "Erreur: " << e.what() << std::endl;
                }
                break;
            }
            case 6: {
                double rate = Utils::readDouble("Taux de remise (%): ", 0.0, 100.0);
                cart.setDiscountRate(rate / 100.0);
                std::cout << "Remise de " << rate << "% appliquee." << std::endl;
                break;
            }
            case 7:
                checkout(customerId);
                break;
            case 0:
                shopping = false;
                break;
        }
    }
}

void ECommercePlatform::addToCart(int customerId) {
    Cart& cart = customerCarts[customerId];
    int productId = Utils::readInt("ID produit: ", 1, 9999);
    int quantity = Utils::readInt("Quantite: ", 1, 1000);

    auto product = stockManager.findProduct(productId);
    if (!product) {
        std::cout << "Produit non trouve." << std::endl;
        return;
    }

    try {
        cart += CartItem(product, quantity);
        std::cout << "\n✅ Ajoute au panier: " << product->getName() 
                  << " x" << quantity << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Erreur: " << e.what() << std::endl;
    }
}

void ECommercePlatform::viewCart(int customerId) {
    Cart& cart = customerCarts[customerId];
    std::cout << cart << std::endl;
    printCartSummary(cart);
}

void ECommercePlatform::checkout(int customerId) {
    Cart& cart = customerCarts[customerId];
    auto customer = findCustomer(customerId);

    if (cart.getItems().empty()) {
        std::cout << "Panier vide!" << std::endl;
        return;
    }

    // Verify stock availability
    for (const auto& item : cart.getItems()) {
        auto product = stockManager.findProduct(item.product->getId());
        if (!product || product->getStock() < item.quantity) {
            std::cout << "Stock insuffisant pour: " << item.product->getName() << std::endl;
            return;
        }
    }

    // Calculate totals
    double subtotal = cart.getTotal();
    double discount = subtotal * cart.getDiscountRate();
    double taxable = subtotal - discount;
    double tax = taxable * 0.20; // 20% TVA
    double total = taxable + tax;

    // Reserve stock
    for (const auto& item : cart.getItems()) {
        stockManager.reserveStock(item.product->getId(), item.quantity);
    }

    // Create order
    int orderId = nextOrderId++;
    auto order = std::make_shared<Order>(orderId, customerId, cart.getItems(),
                                         subtotal, tax, discount, total);
    orders.push_back(order);
    customer->addOrder(order);

    // Generate receipt
    generateOrderReceipt(*order);

    // Clear cart
    cart.clear();

    std::cout << "\n✅ Commande #" << orderId << " confirmee!" << std::endl;
}

void ECommercePlatform::handleOrders() {
    std::cout << "\n--- Gestion des Commandes ---" << std::endl;
    std::cout << "1. Voir toutes les commandes" << std::endl;
    std::cout << "2. Voir commandes par client" << std::endl;
    std::cout << "3. Mettre a jour statut" << std::endl;
    std::cout << "4. Recu de commande" << std::endl;
    std::cout << "0. Retour" << std::endl;

    int choice = Utils::readInt("Choix: ", 0, 4);

    switch (choice) {
        case 1: {
            std::cout << "\n========== TOUTES LES COMMANDES ==========" << std::endl;
            if (orders.empty()) {
                std::cout << "Aucune commande." << std::endl;
                break;
            }
            for (const auto& order : orders) {
                std::cout << *order << std::endl;
            }
            break;
        }
        case 2: {
            int cid = Utils::readInt("ID client: ", 1, 9999);
            auto customer = findCustomer(cid);
            if (customer) {
                customer->displayOrderHistory();
            } else {
                std::cout << "Client non trouve." << std::endl;
            }
            break;
        }
        case 3:
            updateOrderStatus();
            break;
        case 4: {
            int oid = Utils::readInt("ID commande: ", 1000, 9999);
            auto order = findOrder(oid);
            if (order) {
                generateOrderReceipt(*order);
            } else {
                std::cout << "Commande non trouvee." << std::endl;
            }
            break;
        }
    }
}

void ECommercePlatform::updateOrderStatus() {
    int orderId = Utils::readInt("ID commande: ", 1000, 9999);
    auto order = findOrder(orderId);
    if (!order) {
        std::cout << "Commande non trouvee." << std::endl;
        return;
    }

    std::cout << "Statut actuel: " << order->statusToString() << std::endl;
    std::cout << "1. Avancer le statut" << std::endl;
    std::cout << "2. Annuler" << std::endl;
    std::cout << "0. Retour" << std::endl;

    int choice = Utils::readInt("Choix: ", 0, 2);
    if (choice == 1) {
        order->advanceStatus();
        if (order->getStatus() == OrderStatus::DELIVERED) {
            order->setDeliveryDate(Utils::getCurrentDate());
        }
        std::cout << "Nouveau statut: " << order->statusToString() << std::endl;
    } else if (choice == 2) {
        order->setStatus(OrderStatus::CANCELLED);
        // Release stock
        for (const auto& item : order->getItems()) {
            stockManager.releaseStock(item.product->getId(), item.quantity);
        }
        std::cout << "Commande annulee. Stock restitue." << std::endl;
    }
}

void ECommercePlatform::handleRecommendations() {
    if (customers.empty()) {
        std::cout << "\nAucun client inscrit." << std::endl;
        return;
    }

    listCustomers();
    int customerId = Utils::readInt("ID client: ", 1, 9999);
    auto customer = findCustomer(customerId);
    if (!customer) {
        std::cout << "Client non trouve." << std::endl;
        return;
    }

    showRecommendations(customerId);
}

void ECommercePlatform::showRecommendations(int customerId) {
    Cart& cart = customerCarts[customerId];
    auto catalog = stockManager.getAllProducts();

    std::cout << "\n--- Moteur de Recommandation ---" << std::endl;
    std::cout << "Analyse du panier actuel..." << std::endl;

    auto recommendations = recommendationEngine.getRecommendations(cart, catalog, 5);
    recommendationEngine.displayRecommendations(recommendations, std::cout);
    printEngineStats(recommendationEngine, recommendations);
}

void ECommercePlatform::saveData() {
    stockManager.saveToFile("data/products.dat");

    std::ofstream customerFile("data/customers.dat");
    for (const auto& customer : customers) {
        customerFile << customer->serialize() << std::endl;
    }
    customerFile.close();

    std::ofstream orderFile("data/orders.dat");
    for (const auto& order : orders) {
        orderFile << order->serialize() << std::endl;
    }
    orderFile.close();
}

void ECommercePlatform::loadData() {
    stockManager.loadFromFile("data/products.dat");

    // Load customers
    std::ifstream customerFile("data/customers.dat");
    std::string line;
    while (std::getline(customerFile, line)) {
        auto parts = Utils::split(line, '|');
        if (parts[0] == "CUSTOMER") {
            auto customer = std::make_shared<Customer>();
            customer->deserialize(parts);
            customers.push_back(customer);
            customerCarts[customer->getId()] = Cart();
        }
    }
}

void ECommercePlatform::initializeDemoData() {
    // Electronics
    stockManager.addProduct(std::make_shared<Electronics>(
        stockManager.getNextId(), "Smartphone X12", "Telephone haut de gamme",
        899.99, 15, "TechCorp", 24, 25.0));
    stockManager.addProduct(std::make_shared<Electronics>(
        stockManager.getNextId(), "Laptop Pro", "Ordinateur portable professionnel",
        1299.99, 8, "CompuTech", 36, 65.0));
    stockManager.addProduct(std::make_shared<Electronics>(
        stockManager.getNextId(), "Ecouteurs BT", "Ecouteurs sans fil",
        149.99, 30, "SoundMax", 12, 5.0));
    stockManager.addProduct(std::make_shared<Electronics>(
        stockManager.getNextId(), "Tablette 10", "Tablette 10 pouces",
        399.99, 12, "TechCorp", 24, 15.0));

    // Food
    stockManager.addProduct(std::make_shared<Food>(
        stockManager.getNextId(), "Cafe Arabica", "Cafe premium",
        12.99, 50, "2026-12-31", 0, true));
    stockManager.addProduct(std::make_shared<Food>(
        stockManager.getNextId(), "Chocolat Noir", "Chocolat 85% cacao",
        4.99, 100, "2026-08-15", 520, true));
    stockManager.addProduct(std::make_shared<Food>(
        stockManager.getNextId(), "Pates Italiennes", "Pates bio",
        2.49, 200, "2027-01-01", 350, true));
    stockManager.addProduct(std::make_shared<Food>(
        stockManager.getNextId(), "Jus Orange", "Jus frais presse",
        3.99, 40, "2026-06-15", 120, false));

    // Clothing
    stockManager.addProduct(std::make_shared<Clothing>(
        stockManager.getNextId(), "T-Shirt Basique", "Coton confortable",
        19.99, 60, "M", "Noir", "Coton"));
    stockManager.addProduct(std::make_shared<Clothing>(
        stockManager.getNextId(), "Jean Slim", "Denim stretch",
        59.99, 25, "L", "Bleu", "Denim"));
    stockManager.addProduct(std::make_shared<Clothing>(
        stockManager.getNextId(), "Veste Hiver", "Chaude et impermeable",
        129.99, 10, "XL", "Gris", "Polyester"));
    stockManager.addProduct(std::make_shared<Clothing>(
        stockManager.getNextId(), "Robe Ete", "Legere et elegante",
        49.99, 20, "S", "Rouge", "Linen"));
}

std::shared_ptr<Customer> ECommercePlatform::findCustomer(int id) const {
    for (const auto& customer : customers) {
        if (customer->getId() == id) {
            return customer;
        }
    }
    return nullptr;
}

std::shared_ptr<Order> ECommercePlatform::findOrder(int id) const {
    for (const auto& order : orders) {
        if (order->getId() == id) {
            return order;
        }
    }
    return nullptr;
}

void displayPlatformStats(const ECommercePlatform& platform) {
    std::cout << "\n[Stats Plateforme] Fonctionnalite avancee d'analyse" << std::endl;
}
