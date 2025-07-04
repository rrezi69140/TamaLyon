#include "Lion.h"
#include "WebSocketServer.h"
#include "WebSocketClient.h"
#include <QDebug>
#include <QJsonObject>

LionManager::LionManager(QObject *parent):
    QObject(parent), m_mood("joyeux"), m_connectionStatus("Déconnecté"),
    m_server(nullptr), m_client(nullptr), m_isSleeping(false)
{
    // Initialiser le timer pour la dégradation des stats (toutes les 10 secondes)
    decayTimer.setInterval(10000); // 10 secondes pour voir les changements
    connect(&decayTimer, &QTimer::timeout, this, &LionManager::updateMood);
    decayTimer.start();
    
    // Timer pour faire réapparaître les icônes toutes les 3 secondes
    iconRespawnTimer.setInterval(3000); // 3 secondes
    connect(&iconRespawnTimer, &QTimer::timeout, this, [this]() {
        // Signal pour faire réapparaître les icônes dans l'interface
        qDebug() << "🔄 Icônes rechargées";
    });
    iconRespawnTimer.start();
}

QString LionManager::mood() const {
    return m_mood;
}

QString LionManager::connectionStatus() const {
    return m_connectionStatus;
}

void LionManager::startAsHost() {
    qDebug() << "🟢 Mode serveur WebSocket activé";
    
    if (m_client) {
        delete m_client;
        m_client = nullptr;
    }
    
    m_server = new WebSocketServer(this);
    m_server->startServer(12345);
    
    m_connectionStatus = "Serveur actif";
    emit connectionStatusChanged();
}

void LionManager::joinAsClient() {
    qDebug() << "🟡 Mode client WebSocket activé";
    
    if (m_server) {
        delete m_server;
        m_server = nullptr;
    }
    
    m_client = new WebSocketClient(this);
    m_client->connectToServer(QUrl("ws://localhost:12345"));
    
    m_connectionStatus = "Client connecté";
    emit connectionStatusChanged();
}

void LionManager::feed(int amount) {
    if (m_isSleeping) {
        qDebug() << "😴 Le lion dort, il ne peut pas manger";
        return;
    }
    m_hunger = qMin(10, m_hunger + amount);
    qDebug() << "🍖 Lion nourri! Faim:" << m_hunger;
    updateMood();
}

void LionManager::water(int amount) {
    if (m_isSleeping) {
        qDebug() << "😴 Le lion dort, il ne peut pas boire";
        return;
    }
    m_thirst = qMin(10, m_thirst + amount);
    qDebug() << "💧 Lion abreuvé! Soif:" << m_thirst;
    updateMood();
}

void LionManager::pet(int amount) {
    // Les caresses peuvent réveiller le lion
    if (m_isSleeping) {
        qDebug() << "🎾 Caresse réveil le lion!";
        m_isSleeping = false;
    }
    m_affection = qMin(10, m_affection + amount);
    qDebug() << "🎾 Lion caressé! Affection:" << m_affection;
    updateMood();
}

void LionManager::sendCommand(const QString &cmd) {
    processCommand(cmd);
}

void LionManager::processCommand(const QString &cmd) {
    qDebug() << "Processing command:" << cmd;
    
    if (cmd == "feed") {
        m_hunger = qMin(10, m_hunger + 2);
    } else if (cmd == "drink") {
        m_thirst = qMin(10, m_thirst + 2);
    } else if (cmd == "play") {
        m_affection = qMin(10, m_affection + 2);
    }
    
    updateMood();
    
    // Émettre l'état vers le serveur/client
    QJsonObject state;
    state["hunger"] = m_hunger;
    state["thirst"] = m_thirst;
    state["affection"] = m_affection;
    state["mood"] = m_mood;
    emit sendState(state);
}

void LionManager::updateFromState(const QJsonObject &state) {
    if (state.contains("hunger")) m_hunger = state["hunger"].toInt();
    if (state.contains("thirst")) m_thirst = state["thirst"].toInt();
    if (state.contains("affection")) m_affection = state["affection"].toInt();
    if (state.contains("mood")) {
        QString newMood = state["mood"].toString();
        if (m_mood != newMood) {
            m_mood = newMood;
            emit moodChanged();
        }
    }
}

void LionManager::updateMood() {
    QString oldMood = m_mood;
    
    // La faim et la soif se dégradent toujours avec le temps
    m_hunger = qMax(0, m_hunger - 1);
    m_thirst = qMax(0, m_thirst - 1);
    
    // L'affection ne se dégrade que si le lion ne dort pas
    if (!m_isSleeping) {
        m_affection = qMax(0, m_affection - 1);
    }
    
    // Déterminer l'humeur selon les nouvelles règles
    if (m_hunger <= 1 || m_thirst <= 1) {
        // Priorité absolue : faim/soif critique
        m_mood = "affame";
        m_isSleeping = false;
    } else if (m_affection <= 2 && !m_isSleeping) {
        // Si manque d'attention, devient triste puis s'endort
        m_mood = "triste";
    } else if (m_affection <= 1) {
        // Très peu d'attention -> le lion s'endort
        m_mood = "endormi";
        m_isSleeping = true;
        qDebug() << "😴 Le lion s'endort par manque d'attention";
    } else if (m_hunger >= 7 && m_thirst >= 7 && m_affection >= 7) {
        // Tout va bien
        m_mood = "joyeux";
        m_isSleeping = false;
    } else if (m_hunger >= 4 && m_thirst >= 4 && m_affection >= 4) {
        // État correct
        m_mood = "joyeux";
        m_isSleeping = false;
    } else {
        // État moyen
        m_mood = "triste";
        m_isSleeping = false;
    }
    
    if (oldMood != m_mood) {
        emit moodChanged();
        qDebug() << "🦁 Humeur changée:" << m_mood << "| Faim:" << m_hunger << "| Soif:" << m_thirst << "| Affection:" << m_affection << "| Dort:" << m_isSleeping;
    }
}


