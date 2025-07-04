#ifndef LIONMANAGER_H
#define LIONMANAGER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QJsonObject>

class LionManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString mood READ mood NOTIFY moodChanged)
    Q_PROPERTY(QString connectionStatus READ connectionStatus NOTIFY connectionStatusChanged)

public:
    explicit LionManager(QObject *parent = nullptr);

    QString mood() const;
    QString connectionStatus() const;

    Q_INVOKABLE void sendCommand(const QString &cmd);
    Q_INVOKABLE void startAsHost();
    Q_INVOKABLE void joinAsClient();
    Q_INVOKABLE void feed(int amount);
    Q_INVOKABLE void water(int amount);
    Q_INVOKABLE void pet(int amount);

signals:
    void moodChanged();
    void connectionStatusChanged();
    void sendState(const QJsonObject &state);

public slots:
    void processCommand(const QString &cmd);
    void updateFromState(const QJsonObject &state);
    void updateMood();

private:
    QString m_mood;
    QString m_connectionStatus;
    int m_hunger = 5;
    int m_thirst = 5;
    int m_affection = 5;
    bool m_isSleeping = false;

    QTimer decayTimer;
    QTimer iconRespawnTimer;
    
    class WebSocketServer *m_server;
    class WebSocketClient *m_client;
};

#endif // LIONMANAGER_H
