#ifndef LIONMANAGER_H
#define LIONMANAGER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include "WebSocketServer.h"
#include "WebSocketClient.h"

// Forward declaration
class AlimentManager;

class LionManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString mood READ mood WRITE setMood NOTIFY moodChanged)
    Q_PROPERTY(int hunger READ getHunger NOTIFY hungerChanged)
    Q_PROPERTY(int thirst READ getThirst NOTIFY thirstChanged)
    Q_PROPERTY(int affection READ getAffection NOTIFY affectionChanged)
    Q_PROPERTY(int energy READ getEnergy NOTIFY energyChanged)
    Q_PROPERTY(QString connectionStatus READ connectionStatus NOTIFY connectionStatusChanged)

public:
    explicit LionManager(QObject *parent = nullptr);

    QString mood() const;
    void setMood(const QString &newMood);

    int getHunger() const;
    int getThirst() const;
    int getAffection() const;
    int getEnergy() const;
    QString connectionStatus() const;

    Q_INVOKABLE void feed(int points);
    Q_INVOKABLE void giveWater(int points);
    Q_INVOKABLE void pet(int points);
    Q_INVOKABLE void water(int points);
    Q_INVOKABLE void startAsHost();
    Q_INVOKABLE void joinAsClient();
    Q_INVOKABLE void sendCommand(const QString &command);
    Q_INVOKABLE bool isHostMode() const;

    QString generateStateMessage() const;
    
    // Connexion avec AlimentManager
    void setAlimentManager(AlimentManager* alimentManager);
    
    // Méthode pour diffuser l'état actuel
    void broadcastCurrentState();

signals:
    void moodChanged();
    void hungerChanged();
    void thirstChanged();
    void affectionChanged();
    void energyChanged();
    void connectionStatusChanged();
    void stateUpdated(const QString &state);

private slots:
    void decayStates();

private:
    QString m_mood;
    QString m_connectionStatus;
    int hunger;
    int thirst;
    int affection;
    int energy;
    QTimer decayTimer;
    
    // WebSocket components
    WebSocketServer *server;
    WebSocketClient *client;
    bool isHost;
    
    // Référence à AlimentManager
    AlimentManager* m_alimentManager;

    void updateMood();
    void broadcastState();

private slots:
    void onCommandReceived(const QString &command);
    void onStateReceived(const QJsonObject &state);
};

#endif // LIONMANAGER_H
