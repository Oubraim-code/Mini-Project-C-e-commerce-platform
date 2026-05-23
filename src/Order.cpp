#include "Order.h"
#include "Utils.h"
#include <iomanip>

Order::Order() : id(0), customerId(0), subtotal(0.0), tax(0.0), 
                 discount(0.0), total(0.0), status(OrderStatus::PENDING) {}

Order::Order(int id, int customerId, const std::vector<CartItem>& items,
             double subtotal, double tax, double discount, double total)
    : id(id), customerId(customerId), items(items), subtotal(subtotal),
      tax(tax), discount(discount), total(total), status(OrderStatus::PENDING),
      orderDate(Utils::getCurrentDate()) {}

int Order::getId() const { return id; }
int Order::getCustomerId() const { return customerId; }
double Order::getTotal() const { return total; }
OrderStatus Order::getStatus() const { return status; }
std::string Order::getOrderDate() const { return orderDate; }
std::string Order::getDeliveryDate() const { return deliveryDate; }
const std::vector<CartItem>& Order::getItems() const { return items; }

void Order::setStatus(OrderStatus newStatus) { status = newStatus; }
void Order::setDeliveryDate(const std::string& date) { deliveryDate = date; }

void Order::advanceStatus() {
    switch (status) {
        case OrderStatus::PENDING: status = OrderStatus::PROCESSING; break;
        case OrderStatus::PROCESSING: status = OrderStatus::SHIPPED; break;
        case OrderStatus::SHIPPED: status = OrderStatus::DELIVERED; break;
        case OrderStatus::DELIVERED: 
        case OrderStatus::CANCELLED: break;
    }
}

std::string Order::statusToString() const {
    switch (status) {
        case OrderStatus::PENDING: return "En attente";
        case OrderStatus::PROCESSING: return "En traitement";
        case OrderStatus::SHIPPED: return "Expedie";
        case OrderStatus::DELIVERED: return "Livre";
        case OrderStatus::CANCELLED: return "Annule";
        default: return "Inconnu";
    }
}

bool Order::operator<(const Order& other) const {
    return total < other.total;
}

void generateOrderReceipt(const Order& order) {
    std::cout << "\n╔════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           RECU DE COMMANDE                       ║" << std::endl;
    std::cout << "╠════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Commande #" << std::left << std::setw(37) << order.id << "║" << std::endl;
    std::cout << "║ Date: " << std::setw(42) << order.orderDate << "║" << std::endl;
    std::cout << "║ Statut: " << std::setw(40) << order.statusToString() << "║" << std::endl;
    std::cout << "╠════════════════════════════════════════════════╣" << std::endl;

    for (const auto& item : order.items) {
        std::cout << "║ " << std::left << std::setw(3) << item.quantity << " x " 
                  << std::setw(25) << item.product->getName()
                  << std::right << std::setw(15) << std::fixed << std::setprecision(2)
                  << (item.product->getPrice() * item.quantity) << " € ║" << std::endl;
    }

    std::cout << "╠════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ " << std::left << std::setw(35) << "Sous-total:"
              << std::right << std::setw(12) << order.subtotal << " € ║" << std::endl;
    std::cout << "║ " << std::setw(35) << "TVA (20%):"
              << std::setw(12) << order.tax << " € ║" << std::endl;
    if (order.discount > 0) {
        std::cout << "║ " << std::setw(35) << "Remise:"
                  << std::setw(12) << order.discount << " € ║" << std::endl;
    }
    std::cout << "║ " << std::setw(35) << "TOTAL:"
              << std::setw(12) << order.total << " € ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
}

std::string Order::serialize() const {
    std::string result = "ORDER|" + std::to_string(id) + "|" + std::to_string(customerId) + "|" +
                         std::to_string(subtotal) + "|" + std::to_string(tax) + "|" +
                         std::to_string(discount) + "|" + std::to_string(total) + "|" +
                         std::to_string(static_cast<int>(status)) + "|" + orderDate + "|" + deliveryDate;

    for (const auto& item : items) {
        result += "|" + std::to_string(item.product->getId()) + ":" + std::to_string(item.quantity);
    }
    return result;
}

void Order::deserialize(const std::vector<std::string>& data) {
    // Complex deserialization - simplified for demo
    if (data.size() >= 10) {
        id = std::stoi(data[1]);
        customerId = std::stoi(data[2]);
        subtotal = std::stod(data[3]);
        tax = std::stod(data[4]);
        discount = std::stod(data[5]);
        total = std::stod(data[6]);
        status = static_cast<OrderStatus>(std::stoi(data[7]));
        orderDate = data[8];
        deliveryDate = data[9];
    }
}

void Order::display(std::ostream& os) const {
    os << "Commande #" << id << " [" << statusToString() << "]" << std::endl;
    os << "  Client ID: " << customerId << std::endl;
    os << "  Date: " << orderDate << std::endl;
    os << "  Articles: " << items.size() << std::endl;
    os << "  Total: " << std::fixed << std::setprecision(2) << total << " €" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    order.display(os);
    return os;
}

std::ostream& operator<<(std::ostream& os, OrderStatus status) {
    switch (status) {
        case OrderStatus::PENDING: os << "En attente"; break;
        case OrderStatus::PROCESSING: os << "En traitement"; break;
        case OrderStatus::SHIPPED: os << "Expedie"; break;
        case OrderStatus::DELIVERED: os << "Livre"; break;
        case OrderStatus::CANCELLED: os << "Annule"; break;
    }
    return os;
}
