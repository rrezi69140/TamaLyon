#include "AlimentManager.h"
#include "Lion.h"
#include "LionManager.h"
#include <QDebug>

AlimentManager::AlimentManager(QObject *parent)
    : QObject(parent), m_lion(nullptr), m_lionManager(nullptr)
{
    qDebug() << "[AlimentManager] Initialisation";
    initializeAliments();
}

AlimentManager::~AlimentManager()
{
    qDebug() << "[AlimentManager] Destruction";
    qDeleteAll(m_aliments);
    m_aliments.clear();
}

void AlimentManager::initializeAliments()
{
    qDebug() << "[AlimentManager] Création des aliments";
    
    // Créer tous les aliments disponibles
    m_aliments.append(new Pomme(this));
    m_aliments.append(new Pizza(this));
    m_aliments.append(new Eau(this));
    m_aliments.append(new Steak(this));
    m_aliments.append(new ChampignonToxique(this));
    m_aliments.append(new Chocolat(this));
    m_aliments.append(new Poisson(this));
    
    qDebug() << "[AlimentManager]" << m_aliments.size() << "aliments créés";
    
    // Afficher la liste des aliments
    for (int i = 0; i < m_aliments.size(); ++i) {
        const Aliment* aliment = m_aliments[i];
        qDebug() << QString("[AlimentManager] %1. %2 %3 - Faim:%4 Soif:%5 Humeur:%6 Toxique:%7")
                    .arg(i)
                    .arg(aliment->getEmoji())
                    .arg(aliment->getNom())
                    .arg(aliment->getFaimImpact())
                    .arg(aliment->getSoifImpact())
                    .arg(aliment->getHumeurImpact())
                    .arg(aliment->getEstToxique() ? "OUI" : "NON");
    }
}

QQmlListProperty<Aliment> AlimentManager::alimentsDisponibles()
{
    return QQmlListProperty<Aliment>(this, &m_aliments, &AlimentManager::alimentCount, &AlimentManager::alimentAt);
}

Aliment* AlimentManager::getAlimentByIndex(int index) const
{
    if (index >= 0 && index < m_aliments.size()) {
        return m_aliments[index];
    }
    qWarning() << "[AlimentManager] Index invalide:" << index;
    return nullptr;
}

Aliment* AlimentManager::getAlimentByName(const QString &nom) const
{
    for (Aliment* aliment : m_aliments) {
        if (aliment->getNom() == nom) {
            return aliment;
        }
    }
    qWarning() << "[AlimentManager] Aliment non trouvé:" << nom;
    return nullptr;
}

int AlimentManager::getAlimentCount() const
{
    return m_aliments.size();
}

QString AlimentManager::getAlimentInfo(int index) const
{
    Aliment* aliment = getAlimentByIndex(index);
    if (aliment) {
        return QString("%1 %2 - %3")
               .arg(aliment->getEmoji())
               .arg(aliment->getNom())
               .arg(aliment->getDescription());
    }
    return "Aliment inconnu";
}

void AlimentManager::setLion(Lion* lion)
{
    m_lion = lion;
    qDebug() << "[AlimentManager] Lion connecté:" << (lion ? lion->getNom() : "null");
}

void AlimentManager::setLionManager(LionManager* lionManager)
{
    m_lionManager = lionManager;
    qDebug() << "[AlimentManager] LionManager connecté:" << (lionManager ? "OUI" : "NON");
}

void AlimentManager::nourrirLion(int alimentIndex) const
{
    qDebug() << "[AlimentManager] 🍽️ TENTATIVE DE NOURRISSAGE - Index:" << alimentIndex;
    
    if (!m_lion) {
        qDebug() << "[AlimentManager] ❌ Aucun lion connecté!";
        return;
    }
    
    if (alimentIndex < 0 || alimentIndex >= m_aliments.size()) {
        qDebug() << "[AlimentManager] ❌ Index d'aliment invalide:" << alimentIndex << "/ Taille:" << m_aliments.size();
        return;
    }
    
    Aliment* aliment = m_aliments[alimentIndex];
    if (!aliment) {
        qDebug() << "[AlimentManager] ❌ Aliment null à l'index:" << alimentIndex;
        return;
    }
    
    // Si on est en mode client, envoyer la commande au serveur SEULEMENT
    if (m_lionManager && !m_lionManager->isHostMode()) {
        qDebug() << "[AlimentManager] � CLIENT - Envoi commande au serveur (pas d'application locale)";
        QString command = QString("aliment:%1").arg(alimentIndex);
        m_lionManager->sendCommand(command);
        return; // Le client ne fait QUE envoyer la commande
    }
    
    // Sinon, on est l'hôte : appliquer et diffuser
    qDebug() << "[AlimentManager] 🏠 HÔTE - Application et diffusion";
    qDebug() << "[AlimentManager] 📊 État AVANT - Faim:" << m_lion->getFaim() << "Soif:" << m_lion->getSoif() << "Humeur:" << m_lion->getHumeur() << "État:" << m_lion->getEtatString();
    
    // Nourrir le lion avec l'aliment
    m_lion->donnerAliment(aliment);
    
    qDebug() << "[AlimentManager] � État APRÈS - Faim:" << m_lion->getFaim() << "Soif:" << m_lion->getSoif() << "Humeur:" << m_lion->getHumeur() << "État:" << m_lion->getEtatString();
    
    // Diffuser l'état mis à jour
    if (m_lionManager) {
        m_lionManager->broadcastCurrentState();
    }
}

void AlimentManager::processClientAlimentCommand(int alimentIndex) const
{
    qDebug() << "[AlimentManager] 🏠 HÔTE - Traitement commande CLIENT - Index:" << alimentIndex;
    
    if (!m_lion) {
        qDebug() << "[AlimentManager] ❌ Aucun lion connecté!";
        return;
    }
    
    if (alimentIndex < 0 || alimentIndex >= m_aliments.size()) {
        qDebug() << "[AlimentManager] ❌ Index d'aliment invalide:" << alimentIndex << "/ Taille:" << m_aliments.size();
        return;
    }
    
    Aliment* aliment = m_aliments[alimentIndex];
    if (!aliment) {
        qDebug() << "[AlimentManager] ❌ Aliment null à l'index:" << alimentIndex;
        return;
    }
    
    qDebug() << "[AlimentManager] 📊 État AVANT - Faim:" << m_lion->getFaim() << "Soif:" << m_lion->getSoif() << "Humeur:" << m_lion->getHumeur() << "État:" << m_lion->getEtatString();
    
    // Nourrir le lion avec l'aliment (l'hôte applique directement)
    m_lion->donnerAliment(aliment);
    
    qDebug() << "[AlimentManager] ✅ État APRÈS - Faim:" << m_lion->getFaim() << "Soif:" << m_lion->getSoif() << "Humeur:" << m_lion->getHumeur() << "État:" << m_lion->getEtatString();
    
    // Diffuser l'état mis à jour à tous les clients
    if (m_lionManager) {
        m_lionManager->broadcastCurrentState();
    }
}

// Fonctions statiques pour QQmlListProperty
qsizetype AlimentManager::alimentCount(QQmlListProperty<Aliment> *list)
{
    auto* manager = qobject_cast<AlimentManager*>(list->object);
    if (manager) {
        return manager->m_aliments.size();
    }
    return 0;
}

Aliment* AlimentManager::alimentAt(QQmlListProperty<Aliment> *list, qsizetype index)
{
    auto* manager = qobject_cast<AlimentManager*>(list->object);
    if (manager && index >= 0 && index < manager->m_aliments.size()) {
        return manager->m_aliments[index];
    }
    return nullptr;
}
