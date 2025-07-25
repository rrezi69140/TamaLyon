#include "LionManager.h"
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
    isHost(false)
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
    // Seul l'hôte fait décrémenter les valeurs
    if (!isHost && client) {
        return; // Le client reçoit les mises à jour du serveur
    }
    
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

    // Broadcast state if we're the host
    if (isHost) {
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

void LionManager::broadcastState() {
    if (server) {
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
    qDebug() << "[LionManager] Commande reçue du client:" << command;
    
    if (command == "feed") {
        feed(10);
    } else if (command == "water") {
        water(10);
    } else if (command == "pet") {
        pet(10);
    }
}

void LionManager::onStateReceived(const QJsonObject &state) {
    qDebug() << "[LionManager] État reçu du serveur:" << state;
    
    // Update local state from server
    hunger = state["hunger"].toInt();
    thirst = state["thirst"].toInt();
    affection = state["affection"].toInt();
    energy = state["energy"].toInt();
    
    emit hungerChanged();
    emit thirstChanged();
    emit affectionChanged();
    emit energyChanged();
    
    setMood(state["mood"].toString());
}
