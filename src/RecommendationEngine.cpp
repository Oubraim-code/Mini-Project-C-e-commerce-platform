#include "RecommendationEngine.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

std::vector<Recommendation> RecommendationEngine::getRecommendations(
    const Cart& cart,
    const std::vector<std::shared_ptr<Product>>& catalog,
    int maxResults
) const {

    std::vector<Recommendation> recommendations;

    // Get products already in cart to exclude them
    std::vector<int> cartProductIds;
    for (const auto& item : cart.getItems()) {
        cartProductIds.push_back(item.product->getId());
    }

    // For each product in catalog, compute similarity score
    // PURE POLYMORPHISM: each concrete product type computes its own score
    // NO if/switch on concrete types - only virtual method calls
    for (const auto& product : catalog) {
        // Skip products already in cart
        if (std::find(cartProductIds.begin(), cartProductIds.end(), 
                      product->getId()) != cartProductIds.end()) {
            continue;
        }

        // Skip out of stock products
        if (product->getStock() <= 0) {
            continue;
        }

        // POLYMORPHIC CALL: product knows how to compute its own similarity
        // Electronics, Food, Clothing each have their own algorithm
        double score = product->computeSimilarityScore(cart);

        recommendations.push_back({product, score});
    }

    // Sort by score descending
    std::sort(recommendations.begin(), recommendations.end(),
              [](const Recommendation& a, const Recommendation& b) {
                  return a.score > b.score;
              });

    // Limit results
    if (recommendations.size() > static_cast<size_t>(maxResults)) {
        recommendations.resize(maxResults);
    }

    return recommendations;
}

void RecommendationEngine::displayRecommendations(
    const std::vector<Recommendation>& recs, 
    std::ostream& os
) const {
    if (recs.empty()) {
        os << "\nAucune recommandation disponible." << std::endl;
        return;
    }

    os << "\n========== RECOMMANDATIONS ==========" << std::endl;
    os << std::left << std::setw(5) << "Rang"
       << std::setw(25) << "Produit"
       << std::setw(15) << "Type"
       << std::setw(12) << "Prix"
       << std::setw(12) << "Score" << std::endl;
    os << std::string(69, '-') << std::endl;

    int rank = 1;
    for (const auto& rec : recs) {
        os << std::left << std::setw(5) << rank++
           << std::setw(25) << rec.product->getName()
           << std::setw(15) << rec.product->getType()
           << std::setw(12) << std::fixed << std::setprecision(2) << rec.product->getPrice() << " €"
           << std::setw(11) << std::fixed << std::setprecision(1) << rec.score << "%" << std::endl;
    }
    os << "=====================================" << std::endl;
}

void printEngineStats(const RecommendationEngine& engine, 
                       const std::vector<Recommendation>& recs) {
    if (recs.empty()) return;

    double avgScore = 0.0;
    for (const auto& rec : recs) {
        avgScore += rec.score;
    }
    avgScore /= recs.size();

    std::cout << "\n[Stats Moteur] " << recs.size() << " recommandations, "
              << "score moyen: " << std::fixed << std::setprecision(1) 
              << avgScore << "%" << std::endl;
}
