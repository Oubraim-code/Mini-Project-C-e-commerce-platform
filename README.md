# Mini-Amazon - Plateforme E-Commerce C++

## Description

Mini-Amazon est une application console de simulation de plateforme de vente en ligne développée en C++ moderne dans le cadre du module de Programmation Orientée Objet.

Le projet met en œuvre les concepts fondamentaux de la POO en C++ : héritage, polymorphisme, surcharge d'opérateurs, fonctions amies, et gestion de la mémoire avec des smart pointers.

## Fonctionnalités

### Gestion des Produits
- Catalogue multi-catégories : Électronique, Alimentaire, Vêtements
- Ajout, suppression et recherche de produits
- Suivi des stocks avec alertes de rupture
- Persistance des données dans des fichiers

### Gestion des Clients
- Inscription des clients
- Historique des commandes par client
- Détails complets des profils

### Panier et Commandes
- Ajout/suppression/modification des articles
- Calcul automatique du total (prix, TVA 20%, remises)
- Validation des commandes avec mise à jour des stocks
- Suivi des statuts : En attente → En traitement → Expédié → Livré
- Génération de reçus de commande

### Moteur de Recommandation (Challenge Avancé)
- Système entièrement polymorphique
- Chaque type de produit calcule son propre score de similarité
- **Aucune structure conditionnelle (if/switch) sur les types concrets**
- Recommandations basées sur le contenu du panier actuel

## Architecture

### Diagramme des Classes (simplifié)

```
Product (classe abstraite)
├── Electronics
├── Food
└── Clothing

Cart
├── CartItem

Order
├── OrderStatus (enum)

Customer

StockManager (Singleton)

RecommendationEngine

ECommercePlatform (classe principale)
```

### Concepts POO Utilisés

| Concept | Implémentation |
|---------|---------------|
| **Héritage** | Electronics, Food, Clothing héritent de Product |
| **Polymorphisme** | Méthodes virtuelles pures dans Product |
| **Surcharge d'opérateurs** | `==`, `<`, `<<`, `+=`, `-=`, `[]` |
| **Fonctions amies** | `applyDiscount`, `displayCustomerDetails`, `generateOrderReceipt` |
| **Smart Pointers** | `std::shared_ptr` pour la gestion mémoire |
| **Singleton** | StockManager |

## Prérequis

- CMake ≥ 3.14
- Compilateur C++17 (GCC, Clang, MSVC)
- Git

## Installation

### Cloner le dépôt
```bash
git clone https://github.com/votre-username/mini-amazon.git
cd mini-amazon
```

### Compilation avec CMake
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Exécution
```bash
./MiniAmazon
```

## Structure du Projet

```
mini-amazon/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── include/
│   ├── Cart.h
│   ├── Clothing.h
│   ├── Customer.h
│   ├── ECommercePlatform.h
│   ├── Electronics.h
│   ├── Food.h
│   ├── Order.h
│   ├── Product.h
│   ├── RecommendationEngine.h
│   ├── StockManager.h
│   └── Utils.h
├── src/
│   ├── Cart.cpp
│   ├── Clothing.cpp
│   ├── Customer.cpp
│   ├── ECommercePlatform.cpp
│   ├── Electronics.cpp
│   ├── Food.cpp
│   ├── main.cpp
│   ├── Order.cpp
│   ├── Product.cpp
│   ├── RecommendationEngine.cpp
│   ├── StockManager.cpp
│   └── Utils.cpp
└── data/
    └── (fichiers de données générés automatiquement)
```

## Utilisation

### Menu Principal
1. **Gestion des produits** - Consulter/ajouter le catalogue
2. **Gestion des clients** - Inscrire/consulter les clients
3. **Shopping** - Gérer le panier et passer commande
4. **Gestion des commandes** - Suivi et reçus
5. **Recommandations** - Suggestions basées sur le panier
6. **Sauvegarder et quitter**

### Exemple de Session
```
1. Inscrire un client → ID: 1, Nom: Dupont
2. Voir catalogue → Choisir Smartphone X12 (ID: 100)
3. Ajouter au panier → ID: 100, Qté: 2
4. Voir panier → Confirmer le total
5. Passer commande → Reçu généré
6. Voir recommandations → Suggestions basées sur le panier
```

## Challenge Avancé : Polymorphisme Pur

Le moteur de recommandation utilise exclusivement le polymorphisme dynamique :

```cpp
// Dans RecommendationEngine::getRecommendations()
// PAS DE if/switch sur le type concret !
double score = product->computeSimilarityScore(cart);

// Chaque classe concrète implémente sa propre logique :
// - Electronics : proximité prix + affinité électronique
// - Food : préférence bio + proximité calorique
// - Clothing : taille/couleur + ratio vêtements
```

## Auteurs

- [Votre Nom] - Développement et conception
- [Coéquipier 2] - Tests et documentation
- [Coéquipier 3] - Rapport et présentation

## Licence

Projet académique - Module Programmation Orientée Objet C++
