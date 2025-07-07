#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "LionManager.h"
#include "WebSocketServer.h"
#include "WebSocketClient.h"
#include "Lion.h"
#include "AlimentManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Créer les instances principales
    LionManager lionManager;
    Lion lion("Simba");
    AlimentManager alimentManager;
    
    // Connecter l'AlimentManager au Lion
    alimentManager.setLion(&lion);

    // Exposer les classes au QML
    engine.rootContext()->setContextProperty("lionManager", &lionManager);
    engine.rootContext()->setContextProperty("lion", &lion);
    engine.rootContext()->setContextProperty("alimentManager", &alimentManager);

    qDebug() << "[main] 🚀 TamaLyon démarré avec la nouvelle architecture OOP";

    const QUrl url(QStringLiteral("qrc:/MainOOP.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && objUrl == url)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
