#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

// Includes avec nouvelle structure
#include "src/managers/LionManager.h"
#include "src/network/WebSocketServer.h"
#include "src/network/WebSocketClient.h"
#include "src/core/Lion.h"
#include "src/managers/AlimentManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // Créer les instances principales
    LionManager lionManager;
    Lion lion("Simba");
    AlimentManager alimentManager;
    
    // Connecter l'AlimentManager au Lion et au LionManager
    alimentManager.setLion(&lion);
    alimentManager.setLionManager(&lionManager);
    lionManager.setAlimentManager(&alimentManager);
    
    // NOUVEAU: Connecter LionManager aux changements du Lion pour synchroniser les valeurs
    QObject::connect(&lionManager, &LionManager::hungerChanged, [&lionManager, &lion]() {
        int currentFaim = lion.getFaim();
        int targetFaim = lionManager.getHunger();
        lion.appliquerEffetFaim(targetFaim - currentFaim);
        qDebug() << "[main] 🔄 Sync Faim:" << currentFaim << "=>" << targetFaim;
    });
    QObject::connect(&lionManager, &LionManager::thirstChanged, [&lionManager, &lion]() {
        int currentSoif = lion.getSoif();
        int targetSoif = lionManager.getThirst();
        lion.appliquerEffetSoif(targetSoif - currentSoif);
        qDebug() << "[main] 🔄 Sync Soif:" << currentSoif << "=>" << targetSoif;
    });
    QObject::connect(&lionManager, &LionManager::affectionChanged, [&lionManager, &lion]() {
        int currentHumeur = lion.getHumeur();
        int targetHumeur = lionManager.getAffection();
        lion.appliquerEffetHumeur(targetHumeur - currentHumeur);
        qDebug() << "[main] 🔄 Sync Humeur:" << currentHumeur << "=>" << targetHumeur;
    });

    // Exposer les classes au QML
    engine.rootContext()->setContextProperty("lionManager", &lionManager);
    engine.rootContext()->setContextProperty("lion", &lion);
    engine.rootContext()->setContextProperty("alimentManager", &alimentManager);

    qDebug() << "[main] 🚀 TamaLyon démarré avec la nouvelle architecture OOP";

    // Charger la page principale avec la nouvelle structure
    const QUrl url(QStringLiteral("qrc:/qml/qml/pages/MainOOP.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && objUrl == url)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
