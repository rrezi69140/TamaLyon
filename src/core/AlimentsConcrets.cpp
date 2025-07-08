#include "AlimentsConcrets.h"
#include <QDebug>

// ========================================
// Pomme
// ========================================

Pomme::Pomme(QObject *parent) : Aliment(parent)
{
    nom = "Pomme";
    emoji = "🍎";
    categorie = "fruit";
    faimImpact = 8;
    soifImpact = 5;
    humeurImpact = 3;
    estToxique = false;
    
    qDebug() << "[Pomme] Créée:" << nom;
}

QString Pomme::getDescription() const
{
    return "Une pomme rouge et juteuse, riche en vitamines";
}

bool Pomme::estAcceptePar(const QString &typeAnimal) const
{
    // Acceptée par la plupart des animaux
    return typeAnimal == "Lion" || typeAnimal == "Omnivore" || typeAnimal == "Herbivore";
}

// ========================================
// Pizza
// ========================================

Pizza::Pizza(QObject *parent) : Aliment(parent)
{
    nom = "Pizza";
    emoji = "🍕";
    categorie = "sucre"; // Considérée comme sucrée/grasse
    faimImpact = 25;
    soifImpact = -5; // Donne soif
    humeurImpact = 15;
    estToxique = false;
    
    qDebug() << "[Pizza] Créée:" << nom;
}

QString Pizza::getDescription() const
{
    return "Une délicieuse pizza chaude, très nourrissante mais grasse";
}

bool Pizza::estAcceptePar(const QString &typeAnimal) const
{
    // Principalement pour les omnivores
    return typeAnimal == "Lion" || typeAnimal == "Omnivore";
}

// ========================================
// Eau
// ========================================

Eau::Eau(QObject *parent) : Aliment(parent)
{
    nom = "Eau";
    emoji = "💧";
    categorie = "boisson";
    faimImpact = 0;
    soifImpact = 20;
    humeurImpact = 2;
    estToxique = false;
    
    qDebug() << "[Eau] Créée:" << nom;
}

QString Eau::getDescription() const
{
    return "Eau pure et rafraîchissante, essentielle à la vie";
}

bool Eau::estAcceptePar(const QString &/*typeAnimal*/) const
{
    // Tous les animaux ont besoin d'eau
    return true;
}

// ========================================
// Steak
// ========================================

Steak::Steak(QObject *parent) : Aliment(parent)
{
    nom = "Steak";
    emoji = "🥩";
    categorie = "viande";
    faimImpact = 30;
    soifImpact = -3; // La viande donne soif
    humeurImpact = 10;
    estToxique = false;
    
    qDebug() << "[Steak] Créé:" << nom;
}

QString Steak::getDescription() const
{
    return "Un steak juteux et grillé, parfait pour les carnivores";
}

bool Steak::estAcceptePar(const QString &typeAnimal) const
{
    // Principalement pour les carnivores
    return typeAnimal == "Lion" || typeAnimal == "Carnivore" || typeAnimal == "Omnivore";
}

// ========================================
// ChampignonToxique
// ========================================

ChampignonToxique::ChampignonToxique(QObject *parent) : Aliment(parent)
{
    nom = "Champignon Toxique";
    emoji = "🍄";
    categorie = "champignon";
    faimImpact = 5; // Un peu nourrissant
    soifImpact = 0;
    humeurImpact = -15; // Rend triste
    estToxique = true;
    
    qDebug() << "[ChampignonToxique] Créé:" << nom;
}

QString ChampignonToxique::getDescription() const
{
    return "Un champignon vénéneux aux couleurs vives - DANGER!";
}

bool ChampignonToxique::estAcceptePar(const QString &/*typeAnimal*/) const
{
    // Dangereux pour tous, mais certains animaux peuvent être tentés
    return true; // L'animal peut refuser dans sa logique interne
}

// ========================================
// Chocolat
// ========================================

Chocolat::Chocolat(QObject *parent) : Aliment(parent)
{
    nom = "Chocolat";
    emoji = "🍫";
    categorie = "sucre";
    faimImpact = 12;
    soifImpact = -2;
    humeurImpact = 20; // Très bon pour le moral
    estToxique = false;
    
    qDebug() << "[Chocolat] Créé:" << nom;
}

QString Chocolat::getDescription() const
{
    return "Du chocolat délicieux qui remonte le moral";
}

bool Chocolat::estAcceptePar(const QString &typeAnimal) const
{
    // Bon pour les omnivores, mais attention aux carnivores stricts
    return typeAnimal == "Omnivore" || typeAnimal == "Lion";
}

// ========================================
// Poisson
// ========================================

Poisson::Poisson(QObject *parent) : Aliment(parent)
{
    nom = "Poisson";
    emoji = "🐟";
    categorie = "poisson";
    faimImpact = 20;
    soifImpact = 3; // Légèrement hydratant
    humeurImpact = 8;
    estToxique = false;
    
    qDebug() << "[Poisson] Créé:" << nom;
}

QString Poisson::getDescription() const
{
    return "Un poisson frais, riche en protéines et en oméga-3";
}

bool Poisson::estAcceptePar(const QString &typeAnimal) const
{
    // Bon pour les carnivores et omnivores
    return typeAnimal == "Lion" || typeAnimal == "Carnivore" || typeAnimal == "Omnivore";
}
