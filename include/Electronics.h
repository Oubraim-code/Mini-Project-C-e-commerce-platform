#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Product.h"

class Electronics : public Product {
private:
    std::string brand;
    int warrantyMonths;
    double powerConsumption; // in watts

public:
    Electronics();
    Electronics(int id, const std::string& name, const std::string& description,
                double price, int stock, const std::string& brand,
                int warranty, double power);

    // Getters
    std::string getBrand() const;
    int getWarranty() const;
    double getPowerConsumption() const;

    // Setters
    void setBrand(const std::string& newBrand);
    void setWarranty(int months);
    void setPowerConsumption(double watts);

    // Polymorphic implementations
    void display(std::ostream& os) const override;
    std::string getType() const override;
    double computeSimilarityScore(const Cart& cart) const override;
    std::string serialize() const override;
    void deserialize(const std::vector<std::string>& data) override;
};

#endif // ELECTRONICS_H
