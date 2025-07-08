#include "WebSocketClient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

WebSocketClient::WebSocketClient(QObject *parent) : QObject(parent) {}

void WebSocketClient::connectToServer(const QUrl &url) {
    connect(&m_socket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
    connect(&m_socket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onMessageReceived);
    m_socket.open(url);
    qDebug() << "[WebSocketClient] Connexion à" << url;
}

void WebSocketClient::onConnected() {
    qDebug() << "[WebSocketClient] Connecté au serveur";
}

void WebSocketClient::onMessageReceived(const QString &message) {
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (doc.isObject()) {
        emit stateReceived(doc.object());
    }
}

void WebSocketClient::sendCommand(const QString &cmd) {
    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.sendTextMessage(cmd);
        qDebug() << "[WebSocketClient] Commande envoyée:" << cmd;
    }
}
