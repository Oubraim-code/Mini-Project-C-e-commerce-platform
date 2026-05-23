#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

// Forward declaration
class Cart;

class Product {
protected:
    int id;
    std::string name;
    std::string description;
    double price;
    int stock;
    std::string category;

public:
    // Constructors
    Product();
    Product(int id, const std::string& name, const std::string& description,
            double price, int stock, const std::string& category);

    // Virtual destructor for polymorphic behavior
    virtual ~Product() = default;

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    int getStock() const;
    std::string getCategory() const;

    // Setters
    void setName(const std::string& newName);
    void setDescription(const std::string& newDesc);
    void setPrice(double newPrice);
    void setStock(int newStock);

    // Pure virtual methods - polymorphic interface
    virtual void display(std::ostream& os) const = 0;
    virtual std::string getType() const = 0;
    virtual double computeSimilarityScore(const Cart& cart) const = 0;
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::vector<std::string>& data) = 0;

    // Operator overloading
    bool operator==(const Product& other) const;
    bool operator<(const Product& other) const;

    // Friend function for output stream
    friend std::ostream& operator<<(std::ostream& os, const Product& product);

    // Friend function for discount calculation (demonstrates friend usage)
    friend double applyDiscount(const Product& product, double percentage);
};

#endif // PRODUCT_H
