# Rapport de Projet : Mini-Amazon
## Simulation de Plateforme E-Commerce en C++

---

**Module** : Programmation Orientée Objet en C++  
**Durée** : 5 semaines  
**Date** : Mai 2026

---

## Table des Matières

1. Introduction
2. Cahier des Charges
3. Conception
4. Architecture et Diagrammes
5. Description des Classes
6. Concepts POO Mis en Œuvre
7. Challenge Avancé : Moteur de Recommandation
8. Choix Techniques
9. Tests et Validation
10. Conclusion

---

## 1. Introduction

Ce projet consiste en le développement d'une application console simulant une plateforme de vente en ligne (Mini-Amazon). L'objectif est de mettre en pratique les concepts fondamentaux de la Programmation Orientée Objet en C++ moderne, tout en respectant les bonnes pratiques de développement logiciel.

---

## 2. Cahier des Charges

### Fonctionnalités Obligatoires
- Catalogue de produits (électronique, alimentaire, vêtements)
- Gestion du panier et validation des commandes
- Suivi des stocks avec alertes de rupture
- Calcul du montant total (prix, remises, TVA)
- Historique des commandes par client

### Challenge Avancé
Concevoir un moteur de recommandation simplifié où chaque type de produit calcule son score de similarité avec le panier **via le polymorphisme**, sans dépendre de son type concret (pas de if/switch sur les types).

### Outils Obligatoires
- CMake pour la compilation
- GitHub pour le versionnement
- Documentation via README.md

---

## 3. Conception

### Analyse des Besoins
Le système doit gérer trois entités principales :
1. **Produits** : polymorphes, avec comportements spécifiques par catégorie
2. **Clients** : avec historique de commandes
3. **Commandes** : avec cycle de vie et calculs financiers

### Choix Architecturaux
- **Pattern Singleton** pour le gestionnaire de stock
- **Smart Pointers** (`std::shared_ptr`) pour éviter les fuites mémoire
- **Séparation Interface/Implémentation** via headers et sources

---

## 4. Architecture et Diagrammes

### Diagramme de Classes

```
┌─────────────────┐
│   <<abstract>>  │
│    Product      │
├─────────────────┤
│ - id: int       │
│ - name: string  │
│ - price: double │
│ - stock: int    │
├─────────────────┤
│ + display()=0   │
│ + getType()=0   │
│ + computeSimilarity()=0 │
│ + serialize()=0  │
└────────┬────────┘
         │
    ┌────┼────┐
    ▼    ▼    ▼
┌──────┐┌──────┐┌──────┐
│Electr││ Food ││Cloth │
│onics ││      ││ing   │
└──────┘└──────┘└──────┘
```

### Diagramme de Séquence (Commande)

```
Client → Platform: checkout()
Platform → Cart: getItems()
Platform → StockManager: reserveStock()
Platform → Order: create()
Platform → Customer: addOrder()
Cart → Cart: clear()
```

---

## 5. Description des Classes

### Product (Classe Abstraite)
Classe de base pour tous les produits. Définit l'interface polymorphe avec méthodes virtuelles pures.

**Méthodes clés :**
- `display()` : affichage polymorphe
- `computeSimilarityScore()` : calcul du score de recommandation
- `serialize()/deserialize()` : persistance

### Electronics, Food, Clothing
Classes concrètes héritant de Product. Chacune ajoute des attributs spécifiques et implémente ses propres algorithmes de similarité.

### Cart
Gestion du panier avec surcharge d'opérateurs (`+=`, `-=`, `[]`).

### Order
Représentation d'une commande avec enum `OrderStatus` et calculs financiers.

### Customer
Gestion client avec historique des commandes. Utilise `friend` pour l'affichage détaillé.

### StockManager (Singleton)
Gestion centralisée des stocks avec alertes automatiques.

### RecommendationEngine
Moteur de recommandation utilisant uniquement le polymorphisme dynamique.

---

## 6. Concepts POO Mis en Œuvre

### Héritage
```cpp
class Electronics : public Product { ... };
class Food : public Product { ... };
class Clothing : public Product { ... };
```

### Polymorphisme Dynamique
```cpp
std::vector<std::shared_ptr<Product>> catalog;
for (auto& p : catalog) {
    p->display(cout);  // Appel virtuel
}
```

### Surcharge d'Opérateurs
- `operator==` : comparaison de produits
- `operator<` : comparaison par prix
- `operator<<` : affichage stream
- `operator+=` / `-=` : gestion du panier
- `operator[]` : accès aux items

### Fonctions Amies
```cpp
friend double applyDiscount(const Product&, double);
friend void displayCustomerDetails(const Customer&);
friend void generateOrderReceipt(const Order&);
```

### Smart Pointers
Utilisation systématique de `std::shared_ptr` pour éviter les fuites mémoire et simplifier la gestion des objets polymorphes.

---

## 7. Challenge Avancé : Moteur de Recommandation

### Principe
Le moteur de recommandation calcule un score de similarité entre chaque produit du catalogue et le contenu du panier actuel.

### Contrainte Respectée
**Aucune structure conditionnelle (if/switch) sur les types concrets.**

### Implémentation
```cpp
// RecommendationEngine::getRecommendations()
for (const auto& product : catalog) {
    // APPEL POLYMORPHE - chaque type calcule son propre score
    double score = product->computeSimilarityScore(cart);
    recommendations.push_back({product, score});
}
```

### Algorithmes par Type

**Electronics :**
- Proximité de prix (0-30 pts)
- Affinité catégorie (0-40 pts)
- Score de base (30 pts)

**Food :**
- Proximité de prix (0-25 pts)
- Affinité catégorie (0-35 pts)
- Bonus bio (0-20 pts)
- Score de base (20 pts)

**Clothing :**
- Proximité de prix (0-30 pts)
- Affinité catégorie (0-45 pts)
- Bonus matériau (0-15 pts)
- Score de base (10 pts)

---

## 8. Choix Techniques

### CMake
- Compilation modulaire et reproductible
- Gestion des dépendances et des flags de compilation
- C++17 obligatoire

### Git/GitHub
- Branches feature pour le développement
- Commits réguliers et descriptifs
- README.md structuré

### Persistance
- Fichiers texte avec format pipe-delimited
- Sérialisation polymorphe via type tag

### Gestion des Erreurs
- Exceptions pour les cas d'erreur (stock insuffisant, produit non trouvé)
- Validation des entrées utilisateur

---

## 9. Tests et Validation

### Tests Manuels Réalisés
1. Ajout de produits au catalogue
2. Inscription client
3. Ajout au panier avec vérification du stock
4. Passage de commande avec calcul TVA
5. Mise à jour du statut de commande
6. Génération de recommandations
7. Sauvegarde/Chargement des données

### Résultats
Toutes les fonctionnalités ont été validées avec succès. Le moteur de recommandation génère des suggestions cohérentes basées sur le contenu du panier.

---

## 10. Conclusion

Ce projet a permis de consolider les compétences en C++ moderne et POO. Les points clés réussis :

- Architecture modulaire et extensible
- Utilisation correcte du polymorphisme
- Respect du challenge avancé (pas de if/switch sur les types)
- Bonnes pratiques de développement (CMake, Git, documentation)

### Améliorations Futures
- Interface graphique (Qt)
- Base de données SQLite
- API REST
- Système de paiement simulé

---

**Annexes :**
- Code source complet sur GitHub
- Vidéo de démonstration
