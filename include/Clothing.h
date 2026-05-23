#ifndef CLOTHING_H
#define CLOTHING_H

#include "Product.h"

class Clothing : public Product {
private:
    std::string size;
    std::string color;
    std::string material;

public:
    Clothing();
    Clothing(int id, const std::string& name, const std::string& description,
             double price, int stock, const std::string& size,
             const std::string& color, const std::string& material);

    // Getters
    std::string getSize() const;
    std::string getColor() const;
    std::string getMaterial() const;

    // Setters
    void setSize(const std::string& newSize);
    void setColor(const std::string& newColor);
    void setMaterial(const std::string& newMaterial);

    // Polymorphic implementations
    void display(std::ostream& os) const override;
    std::string getType() const override;
    double computeSimilarityScore(const Cart& cart) const override;
    std::string serialize() const override;
    void deserialize(const std::vector<std::string>& data) override;
};

#endif // CLOTHING_H
