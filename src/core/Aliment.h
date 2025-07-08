#ifndef ALIMENT_H
#define ALIMENT_H

#include <QObject>
#include <QString>

/**
 * @brief Classe abstraite représentant un aliment
 * Base pour tous les aliments du jeu avec leurs effets
 */
class Aliment : public QObject {
    Q_OBJECT
    Q_PROPERTY(int faimImpact READ getFaimImpact CONSTANT)
    Q_PROPERTY(int soifImpact READ getSoifImpact CONSTANT)
    Q_PROPERTY(int humeurImpact READ getHumeurImpact CONSTANT)
    Q_PROPERTY(bool estToxique READ getEstToxique CONSTANT)
    Q_PROPERTY(QString categorie READ getCategorie CONSTANT)
    Q_PROPERTY(QString nom READ getNom CONSTANT)
    Q_PROPERTY(QString emoji READ getEmoji CONSTANT)
    Q_PROPERTY(QString description READ getDescription CONSTANT)

public:
    explicit Aliment(QObject *parent = nullptr);
    virtual ~Aliment() = default;

    // Getters
    int getFaimImpact() const { return faimImpact; }
    int getSoifImpact() const { return soifImpact; }
    int getHumeurImpact() const { return humeurImpact; }
    bool getEstToxique() const { return estToxique; }
    QString getCategorie() const { return categorie; }
    QString getNom() const { return nom; }
    QString getEmoji() const { return emoji; }

    // Méthodes virtuelles à implémenter
    virtual QString getDescription() const = 0;
    virtual bool estAcceptePar(const QString &typeAnimal) const = 0;
    virtual int getEmpoisonnementLevel() const { return estToxique ? 10 : 0; }

protected:
    int faimImpact;         // Impact sur la faim (+/-)
    int soifImpact;         // Impact sur la soif (+/-)
    int humeurImpact;       // Impact sur l'humeur (+/-)
    bool estToxique;        // Si l'aliment est toxique
    QString categorie;      // Catégorie (boisson, légume, viande, etc.)
    QString nom;            // Nom de l'aliment
    QString emoji;          // Emoji pour l'affichage
};

#endif // ALIMENT_H
