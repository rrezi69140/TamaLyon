#include "WebSocketServer.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

WebSocketServer::WebSocketServer(QObject *parent)
    : QObject(parent),
    m_server(new QWebSocketServer("LionServer", QWebSocketServer::NonSecureMode, this)) {}

void WebSocketServer::startServer(quint16 port) {
    if (m_server->listen(QHostAddress::Any, port)) {
        qDebug() << "[WebSocketServer] Serveur WebSocket démarré sur le port" << port;
        connect(m_server, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
    } else {
        qWarning() << "[WebSocketServer] Échec de démarrage du serveur.";
    }
}

void WebSocketServer::onNewConnection() {
    QWebSocket *client = m_server->nextPendingConnection();
    qDebug() << "[WebSocketServer] Client connecté:" << client->peerAddress();
    m_clients.insert(client);
    connect(client, &QWebSocket::textMessageReceived, this, &WebSocketServer::onMessageReceived);
    connect(client, &QWebSocket::disconnected, this, &WebSocketServer::onDisconnected);
}

void WebSocketServer::onMessageReceived(const QString &message) {
    qDebug() << "[WebSocketServer] Message reçu:" << message;
    emit commandReceived(message);
}

void WebSocketServer::onDisconnected() {
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client) {
        qDebug() << "[WebSocketServer] Client déconnecté";
        m_clients.remove(client);
        client->deleteLater();
    }
}

void WebSocketServer::broadcastState(const QJsonObject &state) {
    QJsonDocument doc(state);
    QString json = doc.toJson(QJsonDocument::Compact);
    for (QWebSocket *client : m_clients) {
        client->sendTextMessage(json);
    }
}
