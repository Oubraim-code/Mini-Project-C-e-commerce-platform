#ifndef RECOMMENDATIONENGINE_H
#define RECOMMENDATIONENGINE_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Product.h"
#include "Cart.h"

struct Recommendation {
    std::shared_ptr<Product> product;
    double score;

    bool operator>(const Recommendation& other) const {
        return score > other.score;
    }
};

class RecommendationEngine {
public:
    // Core recommendation method using pure polymorphism
    // Each product type computes its own similarity score
    // NO if/switch on concrete types - only virtual dispatch
    std::vector<Recommendation> getRecommendations(
        const Cart& cart,
        const std::vector<std::shared_ptr<Product>>& catalog,
        int maxResults = 5
    ) const;

    // Display recommendations
    void displayRecommendations(const std::vector<Recommendation>& recs, 
                                std::ostream& os) const;

    // Friend function for engine statistics
    friend void printEngineStats(const RecommendationEngine& engine, 
                                  const std::vector<Recommendation>& recs);
};

#endif // RECOMMENDATIONENGINE_H
