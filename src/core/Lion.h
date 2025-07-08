#ifndef LION_H
#define LION_H

#include "Animal.h"
#include "Aliment.h"

/**
 * @brief Classe concrète représentant un Lion
 * Hérite de Animal et implémente les comportements spécifiques
 */
class Lion : public Animal {
    Q_OBJECT

public:
    explicit Lion(const QString &nom = "Simba", QObject *parent = nullptr);
    ~Lion() override = default;

    // Implémentation des méthodes virtuelles
    void reagir(Aliment *aliment) override;
    QString getReactionMessage(Aliment *aliment) const override;
    bool accepteAliment(Aliment *aliment) const override;

protected:
    // Personnalisation des paramètres du lion
    void onEtatChanged(EtatAnimal nouvelEtat) override;
    void onMort() override;
    
    // Paramètres spécifiques au lion
    int getDecroissanceFaim() const override { return 4; }  // Plus rapide que la base
    int getDecroissanceSoif() const override { return 3; }
    int getDecroissanceHumeur() const override { return 2; }
    int getDecroissanceEmpoisonnement() const override { return 2; }  // Résistant

private:
    // Méthodes privées pour les comportements spécifiques
    QString getReactionParCategorie(const QString &categorie) const;
    QString getReactionParEtat() const;
    bool estCarnivorePrefere(const QString &categorie) const;
};

#endif // LION_H
