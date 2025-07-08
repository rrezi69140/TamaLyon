#ifndef ANIMAL_H
#define ANIMAL_H

#include <QObject>
#include <QString>
#include <QTimer>
#include "Aliment.h"

// Forward declaration
class EffectHandler;

/**
 * @brief Énumération des états possibles d'un animal
 */
enum class EtatAnimal {
    Normal,
    Affame,
    Assoiffe,
    Triste,
    Empoisonne,
    Mort
};

/**
 * @brief Classe abstraite représentant un animal
 * Base pour tous les animaux du jeu
 */
class Animal : public QObject {
    Q_OBJECT
    Q_PROPERTY(int faim READ getFaim NOTIFY faimChanged)
    Q_PROPERTY(int soif READ getSoif NOTIFY soifChanged)
    Q_PROPERTY(int humeur READ getHumeur NOTIFY humeurChanged)
    Q_PROPERTY(int empoisonnement READ getEmpoisonnement NOTIFY empoisonnementChanged)
    Q_PROPERTY(bool estMort READ getEstMort NOTIFY estMortChanged)
    Q_PROPERTY(QString etat READ getEtatString NOTIFY etatChanged)
    Q_PROPERTY(QString nom READ getNom CONSTANT)
    Q_PROPERTY(QString type READ getType CONSTANT)

public:
    explicit Animal(const QString &nom, const QString &type, QObject *parent = nullptr);
    virtual ~Animal();

    // Getters
    int getFaim() const { return faim; }
    int getSoif() const { return soif; }
    int getHumeur() const { return humeur; }
    int getEmpoisonnement() const { return empoisonnement; }
    bool getEstMort() const { return estMort; }
    QString getNom() const { return nom; }
    QString getType() const { return type; }
    QString getEtatString() const;
    EtatAnimal getEtat() const { return etat; }

    // Méthodes principales
    Q_INVOKABLE void donnerAliment(Aliment *aliment);
    Q_INVOKABLE void resetAnimal();

    // Méthodes pour les handlers d'effets
    void appliquerEffetFaim(int valeur);
    void appliquerEffetSoif(int valeur);
    void appliquerEffetHumeur(int valeur);
    void appliquerEffetEmpoisonnement(int valeur);

    // Méthodes virtuelles à implémenter
    virtual void reagir(Aliment *aliment) = 0;
    virtual QString getReactionMessage(Aliment *aliment) const = 0;
    virtual bool accepteAliment(Aliment *aliment) const = 0;

signals:
    void faimChanged();
    void soifChanged();
    void humeurChanged();
    void empoisonnementChanged();
    void estMortChanged();
    void etatChanged();
    void reactionAliment(const QString &message);
    void animalMort();

protected slots:
    void decroissance();
    void verifierEtat();

protected:
    // Attributs de base
    int faim;              // 0-100
    int soif;              // 0-100
    int humeur;            // 0-100
    int empoisonnement;    // 0-100
    bool estMort;
    QString nom;
    QString type;
    EtatAnimal etat;

    // Timers
    QTimer *timerDecroissance;
    QTimer *timerEmpoisonnement;

    // Chain of Responsibility
    EffectHandler *effectChain;

    // Méthodes utilitaires
    void setFaim(int valeur);
    void setSoif(int valeur);
    void setHumeur(int valeur);
    void setEmpoisonnement(int valeur);
    void setEtat(EtatAnimal nouvelEtat);
    void mourir();

    // Méthodes virtuelles pour la personnalisation
    virtual void onEtatChanged(EtatAnimal /*nouvelEtat*/) {}
    virtual void onMort() {}
    virtual int getDecroissanceFaim() const { return 3; }
    virtual int getDecroissanceSoif() const { return 4; }
    virtual int getDecroissanceHumeur() const { return 2; }
    virtual int getDecroissanceEmpoisonnement() const { return 1; }
};

#endif // ANIMAL_H
