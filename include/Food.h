#ifndef FOOD_H
#define FOOD_H

#include "Product.h"

class Food : public Product {
private:
    std::string expirationDate;
    int calories;
    bool isOrganic;

public:
    Food();
    Food(int id, const std::string& name, const std::string& description,
         double price, int stock, const std::string& expiry,
         int calories, bool organic);

    // Getters
    std::string getExpirationDate() const;
    int getCalories() const;
    bool getIsOrganic() const;

    // Setters
    void setExpirationDate(const std::string& date);
    void setCalories(int cal);
    void setIsOrganic(bool organic);

    // Polymorphic implementations
    void display(std::ostream& os) const override;
    std::string getType() const override;
    double computeSimilarityScore(const Cart& cart) const override;
    std::string serialize() const override;
    void deserialize(const std::vector<std::string>& data) override;
};

#endif // FOOD_H
