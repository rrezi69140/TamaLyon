#ifndef EFFECTHANDLER_H
#define EFFECTHANDLER_H

#include <QObject>
#include "Aliment.h"

// Forward declaration
class Animal;

/**
 * @brief Classe abstraite pour le pattern Chain of Responsibility
 * Gère les effets des aliments sur les animaux
 */
class EffectHandler : public QObject {
    Q_OBJECT

public:
    explicit EffectHandler(QObject *parent = nullptr);
    virtual ~EffectHandler() = default;

    void setNext(EffectHandler *handler);
    void handleEffect(Animal *animal, Aliment *aliment);

protected:
    virtual void processEffect(Animal *animal, Aliment *aliment) = 0;
    virtual QString getEffectName() const = 0;

private:
    EffectHandler *nextHandler;
};

/**
 * @brief Gestionnaire des effets de faim
 */
class FaimHandler : public EffectHandler {
    Q_OBJECT

public:
    explicit FaimHandler(QObject *parent = nullptr);

protected:
    void processEffect(Animal *animal, Aliment *aliment) override;
    QString getEffectName() const override { return "Faim"; }
};

/**
 * @brief Gestionnaire des effets de soif
 */
class SoifHandler : public EffectHandler {
    Q_OBJECT

public:
    explicit SoifHandler(QObject *parent = nullptr);

protected:
    void processEffect(Animal *animal, Aliment *aliment) override;
    QString getEffectName() const override { return "Soif"; }
};

/**
 * @brief Gestionnaire des effets d'humeur
 */
class HumeurHandler : public EffectHandler {
    Q_OBJECT

public:
    explicit HumeurHandler(QObject *parent = nullptr);

protected:
    void processEffect(Animal *animal, Aliment *aliment) override;
    QString getEffectName() const override { return "Humeur"; }
};

/**
 * @brief Gestionnaire des effets d'empoisonnement
 */
class EmpoisonnementHandler : public EffectHandler {
    Q_OBJECT

public:
    explicit EmpoisonnementHandler(QObject *parent = nullptr);

protected:
    void processEffect(Animal *animal, Aliment *aliment) override;
    QString getEffectName() const override { return "Empoisonnement"; }
};

#endif // EFFECTHANDLER_H
