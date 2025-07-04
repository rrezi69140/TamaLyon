#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QSet>

class WebSocketServer : public QObject {
    Q_OBJECT
public:
    explicit WebSocketServer(QObject *parent = nullptr);
    void startServer(quint16 port);

signals:
    void commandReceived(const QString &cmd);

public slots:
    void broadcastState(const QJsonObject &state);

private slots:
    void onNewConnection();
    void onMessageReceived(const QString &message);
    void onDisconnected();

private:
    QWebSocketServer *m_server;
    QSet<QWebSocket*> m_clients;
};

#endif // WEBSOCKETSERVER_H
