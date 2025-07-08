#include "LionManager.h"
#include "AlimentManager.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>

LionManager::LionManager(QObject *parent)
    : QObject(parent),
    m_mood("joyeux"),
    m_connectionStatus("Non connecté"),
    hunger(100),
    thirst(100),
    affection(100),
    energy(100),
    server(nullptr),
    client(nullptr),
    isHost(false),
    m_alimentManager(nullptr)
{
    decayTimer.setInterval(5000); // toutes les 5 secondes
    connect(&decayTimer, &QTimer::timeout, this, &LionManager::decayStates);
    decayTimer.start();
    updateMood();
    
    // Émettre les signaux initiaux pour que l'interface se mette à jour
    emit hungerChanged();
    emit thirstChanged();
    emit affectionChanged();
    emit energyChanged();
    emit connectionStatusChanged();
}

QString LionManager::mood() const {
    return m_mood;
}

void LionManager::setMood(const QString &newMood) {
    if (m_mood != newMood) {
        m_mood = newMood;
        emit moodChanged();
        qDebug() << "[LionManager] Mood changé en:" << m_mood;
    }
}

void LionManager::feed(int points) {
    hunger = qMin(hunger + points, 100);
    qDebug() << "[LionManager] Nourri +" << points << "=> Hunger:" << hunger;
    emit hungerChanged();
    updateMood();
}

void LionManager::giveWater(int points) {
    thirst = qMin(thirst + points, 100);
    qDebug() << "[LionManager] Bu +" << points << "=> Thirst:" << thirst;
    emit thirstChanged();
    updateMood();
}

void LionManager::pet(int points) {
    affection = qMin(affection + points, 100);
    qDebug() << "[LionManager] Caresse +" << points << "=> Affection:" << affection;
    emit affectionChanged();
    updateMood();
}

void LionManager::decayStates() {
    // Seul l'hôte calcule la décroissance
    if (!isHost) {
        return; // Le client ne fait rien, il attend les updates du serveur
    }
    
    qDebug() << "[LionManager] 🏠 HÔTE - Calcul de la décroissance";
    
    hunger = qMax(hunger - 5, 0);
    thirst = qMax(thirst - 5, 0);
    affection = qMax(affection - 2, 0);
    
    // L'énergie augmente quand le lion dort (affection basse)
    if (affection < 30) {
        energy = qMin(energy + 10, 100);
    } else {
        energy = qMax(energy - 3, 0);
    }

    qDebug() << "[LionManager] Décroissance | Hunger:" << hunger << "Thirst:" << thirst << "Affection:" << affection << "Energy:" << energy;

    emit hungerChanged();
    emit thirstChanged();
    emit affectionChanged();
    emit energyChanged();
    updateMood();
}

void LionManager::updateMood() {
    QString newMood;

    if (hunger < 30) {
        newMood = "affame";
    } else if (thirst < 30) {
        newMood = "triste";
    } else if (affection < 30) {
        newMood = "endormi";
    } else {
        newMood = "joyeux";
    }

    setMood(newMood);

    // Seul l'hôte diffuse l'état
    if (isHost) {
        qDebug() << "[LionManager] 🏠 HÔTE - Diffusion de l'état après changement";
        broadcastState();
    }

    emit stateUpdated(generateStateMessage());
}

QString LionManager::generateStateMessage() const {
    return QString("H:%1 | T:%2 | A:%3 | Mood:%4")
    .arg(hunger)
        .arg(thirst)
        .arg(affection)
        .arg(m_mood);
}

int LionManager::getHunger() const {
    return hunger;
}

int LionManager::getThirst() const {
    return thirst;
}

int LionManager::getAffection() const {
    return affection;
}

int LionManager::getEnergy() const {
    return energy;
}

QString LionManager::connectionStatus() const {
    return m_connectionStatus;
}

void LionManager::startAsHost() {
    m_connectionStatus = "Hébergement...";
    emit connectionStatusChanged();
    qDebug() << "[LionManager] Démarrage en tant qu'hôte";
    
    isHost = true;
    server = new WebSocketServer(this);
    connect(server, &WebSocketServer::commandReceived, this, &LionManager::onCommandReceived);
    server->startServer(9999);
    
    m_connectionStatus = "Hébergement actif (port 9999)";
    emit connectionStatusChanged();
}

void LionManager::joinAsClient() {
    m_connectionStatus = "Connexion...";
    emit connectionStatusChanged();
    qDebug() << "[LionManager] Connexion en tant que client";
    
    isHost = false;
    client = new WebSocketClient(this);
    connect(client, &WebSocketClient::stateReceived, this, &LionManager::onStateReceived);
    client->connectToServer(QUrl("ws://localhost:9999"));
    
    m_connectionStatus = "Connecté au serveur";
    emit connectionStatusChanged();
}

void LionManager::sendCommand(const QString &command) {
    if (client && !isHost) {
        client->sendCommand(command);
        qDebug() << "[LionManager] Commande envoyée au serveur:" << command;
    }
}

bool LionManager::isHostMode() const {
    return isHost;
}

void LionManager::water(int points) {
    giveWater(points);
}

void LionManager::setAlimentManager(AlimentManager* alimentManager)
{
    m_alimentManager = alimentManager;
    qDebug() << "[LionManager] AlimentManager connecté:" << (alimentManager ? "OUI" : "NON");
}

void LionManager::broadcastCurrentState()
{
    if (isHost) {
        qDebug() << "[LionManager] 📢 Diffusion de l'état actuel";
        broadcastState();
    }
}

void LionManager::broadcastState() {
    if (server && m_alimentManager) {
        // Récupérer l'état réel du Lion via AlimentManager
        QJsonObject state;
        state["hunger"] = hunger;
        state["thirst"] = thirst;
        state["affection"] = affection;
        state["energy"] = energy;
        state["mood"] = m_mood;
        
        server->broadcastState(state);
        qDebug() << "[LionManager] État diffusé:" << state;
    }
}

void LionManager::onCommandReceived(const QString &command) {
    qDebug() << "[LionManager] 🏠 HÔTE - Commande reçue du client:" << command;
    
    if (command == "feed") {
        feed(10);
    } else if (command == "water") {
        water(10);
    } else if (command == "pet") {
        pet(10);
    } else if (command.startsWith("aliment:")) {
        // Commande d'aliment venant d'un client
        QString indexStr = command.mid(8); // Enlever "aliment:"
        bool ok;
        int alimentIndex = indexStr.toInt(&ok);
        if (ok && m_alimentManager) {
            qDebug() << "[LionManager] 🍽️ HÔTE - Traitement commande aliment du CLIENT - Index:" << alimentIndex;
            // L'hôte traite la commande du client directement (pas de vérification de mode)
            m_alimentManager->processClientAlimentCommand(alimentIndex);
        } else {
            qDebug() << "[LionManager] ❌ Index d'aliment invalide ou AlimentManager manquant:" << command;
        }
    } else {
        qDebug() << "[LionManager] ⚠️ Commande inconnue:" << command;
    }
}

void LionManager::onStateReceived(const QJsonObject &state) {
    qDebug() << "[LionManager] 📱 CLIENT - État reçu du serveur:" << state;
    
    // Le client applique TOUT ce que le serveur lui envoie
    if (!isHost) {
        int newHunger = state["hunger"].toInt();
        int newThirst = state["thirst"].toInt();
        int newAffection = state["affection"].toInt();
        int newEnergy = state["energy"].toInt();
        QString newMood = state["mood"].toString();
        
        qDebug() << "[LionManager] 📱 CLIENT - Synchronisation:" 
                 << "Hunger:" << hunger << "=>" << newHunger
                 << "Thirst:" << thirst << "=>" << newThirst
                 << "Affection:" << affection << "=>" << newAffection
                 << "Mood:" << m_mood << "=>" << newMood;
        
        hunger = newHunger;
        thirst = newThirst;
        affection = newAffection;
        energy = newEnergy;
        
        emit hungerChanged();
        emit thirstChanged();
        emit affectionChanged();
        emit energyChanged();
        
        setMood(newMood);
        qDebug() << "[LionManager] 🔄 CLIENT - État local synchronisé avec le serveur";
    }
}
