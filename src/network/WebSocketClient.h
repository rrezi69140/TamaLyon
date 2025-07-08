#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>

class WebSocketClient : public QObject {
    Q_OBJECT
public:
    explicit WebSocketClient(QObject *parent = nullptr);
    void connectToServer(const QUrl &url);

public slots:
    void sendCommand(const QString &cmd);

signals:
    void stateReceived(const QJsonObject &state);

private slots:
    void onConnected();
    void onMessageReceived(const QString &message);

private:
    QWebSocket m_socket;
};

#endif // WEBSOCKETCLIENT_H
