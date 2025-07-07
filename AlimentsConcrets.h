#ifndef ALIMENTS_CONCRETS_H
#define ALIMENTS_CONCRETS_H

#include "Aliment.h"

/**
 * @brief Classe pour représenter une pomme
 */
class Pomme : public Aliment {
    Q_OBJECT

public:
    explicit Pomme(QObject *parent = nullptr);
    QString getDescription() const override;
    bool estAcceptePar(const QString &typeAnimal) const override;
};

/**
 * @brief Classe pour représenter une pizza
 */
class Pizza : public Aliment {
    Q_OBJECT

public:
    explicit Pizza(QObject *parent = nullptr);
    QString getDescription() const override;
    bool estAcceptePar(const QString &typeAnimal) const override;
};

/**
 * @brief Classe pour représenter de l'eau
 */
class Eau : public Aliment {
    Q_OBJECT

public:
    explicit Eau(QObject *parent = nullptr);
    QString getDescription() const override;
    bool estAcceptePar(const QString &typeAnimal) const override;
};

/**
 * @brief Classe pour représenter un steak
 */
class Steak : public Aliment {
    Q_OBJECT

public:
    explicit Steak(QObject *parent = nullptr);
    QString getDescription() const override;
    bool estAcceptePar(const QString &typeAnimal) const override;
};

/**
 * @brief Classe pour représenter un champignon toxique
 */
class ChampignonToxique : public Aliment {
    Q_OBJECT

public:
    explicit ChampignonToxique(QObject *parent = nullptr);
    QString getDescription() const override;
    bool estAcceptePar(const QString &typeAnimal) const override;
    int getEmpoisonnementLevel() const override { return 25; }
};

/**
 * @brief Classe pour représenter du chocolat
 */
class Chocolat : public Aliment {
    Q_OBJECT

public:
    explicit Chocolat(QObject *parent = nullptr);
    QString getDescription() const override;
    bool estAcceptePar(const QString &typeAnimal) const override;
};

/**
 * @brief Classe pour représenter du poisson
 */
class Poisson : public Aliment {
    Q_OBJECT

public:
    explicit Poisson(QObject *parent = nullptr);
    QString getDescription() const override;
    bool estAcceptePar(const QString &typeAnimal) const override;
};

#endif // ALIMENTS_CONCRETS_H
