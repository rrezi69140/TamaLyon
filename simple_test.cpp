#include <iostream>
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <QThread>

// Inclure nos classes
#include "Lion.h"
#include "AlimentManager.h"
#include "LionManager.h"
#include "AlimentsConcrets.h"

class SimpleTest : public QObject {
    Q_OBJECT

public:
    SimpleTest() {
        qDebug() << "🧪 === TEST SIMPLE TAMALYON ===";
        
        // Test 1: Création des objets
        testCreation();
        
        // Test 2: Logique métier
        testLogique();
        
        // Test 3: Réseau basique
        QTimer::singleShot(100, this, &SimpleTest::testReseau);
    }

private slots:
    void testCreation() {
        qDebug() << "\n🔧 Test 1: Création des objets";
        
        Lion* lion = new Lion("TestLion", this);
        AlimentManager* alimentManager = new AlimentManager(this);
        LionManager* lionManager = new LionManager(this);
        
        alimentManager->setLion(lion);
        alimentManager->setLionManager(lionManager);
        lionManager->setAlimentManager(alimentManager);
        
        qDebug() << "✅ Objets créés:";
        qDebug() << "   Lion:" << lion->getNom() << "- Faim:" << lion->getFaim();
        qDebug() << "   Aliments disponibles:" << alimentManager->getAlimentCount();
        qDebug() << "   LionManager en mode host:" << lionManager->isHostMode();
    }
    
    void testLogique() {
        qDebug() << "\n🍎 Test 2: Logique métier";
        
        Lion* lion = new Lion("TestLion2", this);
        AlimentManager* alimentManager = new AlimentManager(this);
        alimentManager->setLion(lion);
        
        int faimAvant = lion->getFaim();
        qDebug() << "📊 Faim avant:" << faimAvant;
        
        // Créer une pomme et la donner
        Pomme* pomme = new Pomme(this);
        lion->donnerAliment(pomme);
        
        int faimApres = lion->getFaim();
        qDebug() << "📊 Faim après pomme:" << faimApres;
        qDebug() << (faimApres > faimAvant ? "✅" : "❌") << "La pomme a" << (faimApres > faimAvant ? "augmenté" : "PAS augmenté") << "la faim";
        
        // Test avec AlimentManager
        qDebug() << "\n🔧 Test avec AlimentManager:";
        alimentManager->nourrirLion(0); // Index 0 = Pomme
        
        int faimApres2 = lion->getFaim();
        qDebug() << "📊 Faim après AlimentManager:" << faimApres2;
        qDebug() << (faimApres2 > faimApres ? "✅" : "❌") << "AlimentManager" << (faimApres2 > faimApres ? "fonctionne" : "NE fonctionne PAS");
    }
    
    void testReseau() {
        qDebug() << "\n🌐 Test 3: Réseau basique";
        
        // Créer host
        Lion* hostLion = new Lion("HostLion", this);
        AlimentManager* hostAlimentManager = new AlimentManager(this);
        LionManager* hostManager = new LionManager(this);
        
        hostAlimentManager->setLion(hostLion);
        hostAlimentManager->setLionManager(hostManager);
        hostManager->setAlimentManager(hostAlimentManager);
        
        // Démarrer en mode host
        qDebug() << "🏠 Démarrage host...";
        hostManager->startAsHost();
        
        QTimer::singleShot(1000, this, [=]() {
            qDebug() << "📊 Host mode activé:" << hostManager->isHostMode();
            
            // Créer client
            Lion* clientLion = new Lion("ClientLion", this);
            AlimentManager* clientAlimentManager = new AlimentManager(this);
            LionManager* clientManager = new LionManager(this);
            
            clientAlimentManager->setLion(clientLion);
            clientAlimentManager->setLionManager(clientManager);
            clientManager->setAlimentManager(clientAlimentManager);
            
            qDebug() << "🔗 Connexion client...";
            clientManager->joinAsClient();
            
            QTimer::singleShot(1000, this, [=]() {
                qDebug() << "📊 Client mode:" << (clientManager->isHostMode() ? "HOST (ERROR)" : "CLIENT (OK)");
                
                // Test commande d'aliment
                qDebug() << "\n🍎 Test commande aliment du client:";
                int faimHostAvant = hostLion->getFaim();
                int faimClientAvant = clientLion->getFaim();
                
                qDebug() << "📊 Avant - Host faim:" << faimHostAvant << "Client faim:" << faimClientAvant;
                
                // Le client envoie une commande d'aliment
                clientAlimentManager->nourrirLion(0); // Pomme
                
                QTimer::singleShot(500, this, [=]() {
                    int faimHostApres = hostLion->getFaim();
                    int faimClientApres = clientLion->getFaim();
                    
                    qDebug() << "📊 Après - Host faim:" << faimHostApres << "Client faim:" << faimClientApres;
                    
                    bool hostChange = faimHostApres != faimHostAvant;
                    bool clientSync = faimClientApres == faimHostApres;
                    
                    qDebug() << (hostChange ? "✅" : "❌") << "Host état changé:" << hostChange;
                    qDebug() << (clientSync ? "✅" : "❌") << "Client synchronisé:" << clientSync;
                    
                    qDebug() << "\n🏁 === RÉSULTATS FINAUX ===";
                    if (hostChange && clientSync) {
                        qDebug() << "✅ SYNCHRONISATION FONCTIONNE !";
                    } else {
                        qDebug() << "❌ PROBLÈME DE SYNCHRONISATION";
                        if (!hostChange) qDebug() << "   - Host ne change pas d'état";
                        if (!clientSync) qDebug() << "   - Client pas synchronisé";
                    }
                    
                    QCoreApplication::quit();
                });
            });
        });
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    SimpleTest test;
    
    // Timeout de sécurité
    QTimer::singleShot(10000, &app, &QCoreApplication::quit);
    
    return app.exec();
}

#include "simple_test.moc"
