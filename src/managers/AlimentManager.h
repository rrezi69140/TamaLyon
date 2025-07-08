#ifndef ALIMENTMANAGER_H
#define ALIMENTMANAGER_H

#include <QObject>
#include <QQmlListProperty>
#include <QList>
#include "Aliment.h"
#include "AlimentsConcrets.h"

// Forward declarations
class Lion;
class LionManager;

/**
 * @brief Gestionnaire des aliments pour l'interface QML
 * Fournit les aliments disponibles et gère leur création
 */
class AlimentManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Aliment> alimentsDisponibles READ alimentsDisponibles CONSTANT)

public:
    explicit AlimentManager(QObject *parent = nullptr);
    ~AlimentManager();

    // Méthodes pour connecter le lion et le gestionnaire réseau
    void setLion(Lion* lion);
    void setLionManager(LionManager* lionManager);

    // Propriété pour QML
    QQmlListProperty<Aliment> alimentsDisponibles();

    // Méthodes pour QML
    Q_INVOKABLE Aliment* getAlimentByIndex(int index) const;
    Q_INVOKABLE Aliment* getAlimentByName(const QString &nom) const;
    Q_INVOKABLE int getAlimentCount() const;
    Q_INVOKABLE QString getAlimentInfo(int index) const;
    Q_INVOKABLE void nourrirLion(int alimentIndex) const;
    
    // Méthode spécifique pour l'hôte traitant les commandes clients
    void processClientAlimentCommand(int alimentIndex) const;

signals:
    void alimentsChanged();

private:
    QList<Aliment*> m_aliments;
    Lion* m_lion; // Référence au lion
    LionManager* m_lionManager; // Référence au gestionnaire réseau
    
    void initializeAliments();
    
    // Fonctions statiques pour QQmlListProperty
    static qsizetype alimentCount(QQmlListProperty<Aliment> *list);
    static Aliment* alimentAt(QQmlListProperty<Aliment> *list, qsizetype index);
};

#endif // ALIMENTMANAGER_H
