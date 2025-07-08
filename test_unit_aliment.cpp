#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include "AlimentManager.h"
#include "LionManager.h"
#include "Lion.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    qDebug() << "🧪 === TEST UNITAIRE COMMANDES ALIMENT ===";
    
    // Créer les composants
    LionManager lionManager;
    AlimentManager alimentManager;
    Lion lion("TestLion"); // Constructeur correct
    
    // Connecter les composants
    alimentManager.setLion(&lion);
    alimentManager.setLionManager(&lionManager);
    lionManager.setAlimentManager(&alimentManager);
    
    qDebug() << "✅ Composants créés et connectés";
    
    // Test en mode HOST
    qDebug() << "\n🏠 === TEST MODE HOST ===";
    lionManager.startAsHost();
    
    QTimer::singleShot(1000, [&]() {
        qDebug() << "📊 État initial du lion:";
        qDebug() << "  Faim:" << lion.getFaim();
        qDebug() << "  Soif:" << lion.getSoif();
        qDebug() << "  Humeur:" << lion.getHumeur();
        
        qDebug() << "\n🍎 Test aliment index 0 (Pomme)";
        alimentManager.nourrirLion(0);
        
        QTimer::singleShot(500, [&]() {
            qDebug() << "📊 État après aliment:";
            qDebug() << "  Faim:" << lion.getFaim();
            qDebug() << "  Soif:" << lion.getSoif();
            qDebug() << "  Humeur:" << lion.getHumeur();
            
            qDebug() << "\n✅ Test HOST terminé";
            
            // Test en mode CLIENT avec un nouveau setup
            qDebug() << "\n📱 === TEST MODE CLIENT ===";
            
            // Créer un deuxième AlimentManager pour le client
            AlimentManager clientAlimentManager;
            LionManager clientManager;
            
            // Connecter les composants du client
            clientAlimentManager.setLion(&lion);
            clientAlimentManager.setLionManager(&clientManager);
            clientManager.setAlimentManager(&clientAlimentManager);
            
            qDebug() << "État initial client - isHost:" << clientManager.isHostMode();
            clientManager.joinAsClient();
            qDebug() << "Après joinAsClient - isHost:" << clientManager.isHostMode();
            
            QTimer::singleShot(2000, [&]() {
                qDebug() << "🍕 Test aliment index 1 (Pizza) depuis client";
                qDebug() << "Mode Host du client:" << clientManager.isHostMode();
                clientAlimentManager.nourrirLion(1);
                
                QTimer::singleShot(1000, [&]() {
                    qDebug() << "📊 État final:";
                    qDebug() << "  Faim:" << lion.getFaim();
                    qDebug() << "  Soif:" << lion.getSoif();
                    qDebug() << "  Humeur:" << lion.getHumeur();
                    
                    qDebug() << "\n🧪 Test terminé!";
                    app.quit();
                });
            });
        });
    });
    
    return app.exec();
}
