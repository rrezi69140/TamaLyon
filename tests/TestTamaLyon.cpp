#include "TestTamaLyon.h"
#include <QCoreApplication>
#include <QThread>
#include <QEventLoop>
#include <QTimer>

void TestTamaLyon::initTestCase()
{
    qDebug() << "🧪 === DÉBUT DES TESTS TAMALYON ===";
    qDebug() << "🔧 Initialisation de l'environnement de test...";
    
    // Initialiser les objets de base
    testLion = nullptr;
    testAlimentManager = nullptr;
    testLionManager = nullptr;
}

void TestTamaLyon::cleanupTestCase()
{
    qDebug() << "🧪 === FIN DES TESTS TAMALYON ===";
}

void TestTamaLyon::init()
{
    // Créer des objets frais pour chaque test
    testLion = new Lion("TestLion", this);
    testAlimentManager = new AlimentManager(this);
    testLionManager = new LionManager(this);
    
    // Connecter les objets
    testAlimentManager->setLion(testLion);
    testAlimentManager->setLionManager(testLionManager);
    testLionManager->setAlimentManager(testAlimentManager);
}

void TestTamaLyon::cleanup()
{
    // Nettoyer les objets
    if (testLion) {
        testLion->deleteLater();
        testLion = nullptr;
    }
    if (testAlimentManager) {
        testAlimentManager->deleteLater();
        testAlimentManager = nullptr;
    }
    if (testLionManager) {
        testLionManager->deleteLater();
        testLionManager = nullptr;
    }
}

// ==================== TESTS DE LOGIQUE MÉTIER ====================

void TestTamaLyon::testLionCreation()
{
    qDebug() << "\n🧪 Test: Création du Lion";
    
    QCOMPARE(testLion->getNom(), QString("TestLion"));
    QCOMPARE(testLion->getType(), QString("Lion Africain"));
    QCOMPARE(testLion->getFaim(), 50);
    QCOMPARE(testLion->getSoif(), 50);
    QCOMPARE(testLion->getHumeur(), 50);
    QCOMPARE(testLion->getEmpoisonnement(), 0);
    QCOMPARE(testLion->getEstMort(), false);
    
    qDebug() << "✅ Lion créé correctement avec les valeurs par défaut";
}

void TestTamaLyon::testLionAlimentBasique()
{
    qDebug() << "\n🧪 Test: Alimentation basique du Lion";
    
    // Créer une pomme (impact positif)
    Pomme* pomme = new Pomme(this);
    
    int faimAvant = testLion->getFaim();
    int humeurAvant = testLion->getHumeur();
    
    qDebug() << "📊 État AVANT - Faim:" << faimAvant << "Humeur:" << humeurAvant;
    
    // Donner la pomme au lion
    testLion->donnerAliment(pomme);
    
    int faimApres = testLion->getFaim();
    int humeurApres = testLion->getHumeur();
    
    qDebug() << "📊 État APRÈS - Faim:" << faimApres << "Humeur:" << humeurApres;
    qDebug() << "📈 Changement - Faim: +" << (faimApres - faimAvant) << "Humeur: +" << (humeurApres - humeurAvant);
    
    // Vérifier que les valeurs ont augmenté
    QVERIFY(faimApres > faimAvant);
    QVERIFY(humeurApres >= humeurAvant); // Humeur peut rester la même selon l'aliment
    
    qDebug() << "✅ Alimentation basique fonctionne correctement";
}

void TestTamaLyon::testLionAlimentToxique()
{
    qDebug() << "\n🧪 Test: Aliment toxique";
    
    // Créer un champignon toxique
    ChampignonToxique* champignon = new ChampignonToxique(this);
    
    int empoisonnementAvant = testLion->getEmpoisonnement();
    
    qDebug() << "📊 Empoisonnement AVANT:" << empoisonnementAvant;
    
    // Donner le champignon au lion
    testLion->donnerAliment(champignon);
    
    int empoisonnementApres = testLion->getEmpoisonnement();
    
    qDebug() << "📊 Empoisonnement APRÈS:" << empoisonnementApres;
    qDebug() << "📈 Changement: +" << (empoisonnementApres - empoisonnementAvant);
    
    // Vérifier que l'empoisonnement a augmenté
    QVERIFY(empoisonnementApres > empoisonnementAvant);
    
    qDebug() << "✅ Aliment toxique fonctionne correctement";
}

void TestTamaLyon::testLionDecay()
{
    qDebug() << "\n🧪 Test: Déclin naturel du Lion";
    
    // Mettre le lion à des valeurs élevées
    testLion->setFaim(80);
    testLion->setSoif(80);
    testLion->setHumeur(80);
    
    int faimAvant = testLion->getFaim();
    int soifAvant = testLion->getSoif();
    int humeurAvant = testLion->getHumeur();
    
    qDebug() << "📊 État AVANT decay - Faim:" << faimAvant << "Soif:" << soifAvant << "Humeur:" << humeurAvant;
    
    // Forcer le decay (normalement appelé par le timer)
    testLionManager->decayStates();
    
    int faimApres = testLion->getFaim();
    int soifApres = testLion->getSoif();
    int humeurApres = testLion->getHumeur();
    
    qDebug() << "📊 État APRÈS decay - Faim:" << faimApres << "Soif:" << soifApres << "Humeur:" << humeurApres;
    
    // Vérifier que les valeurs ont diminué
    QVERIFY(faimApres < faimAvant);
    QVERIFY(soifApres < soifAvant);
    QVERIFY(humeurApres < humeurAvant);
    
    qDebug() << "✅ Déclin naturel fonctionne correctement";
}

void TestTamaLyon::testLionMort()
{
    qDebug() << "\n🧪 Test: Mort du Lion";
    
    // Mettre le lion en situation critique
    testLion->setFaim(0);
    testLion->setSoif(0);
    testLion->setEmpoisonnement(100);
    
    // Forcer la mise à jour de l'état
    testLionManager->updateMood();
    
    qDebug() << "📊 État final - EstMort:" << testLion->getEstMort() << "État:" << testLion->getEtatString();
    
    // Le lion devrait être mort
    QVERIFY(testLion->getEstMort());
    
    qDebug() << "✅ Mécanisme de mort fonctionne correctement";
}

void TestTamaLyon::testLionReset()
{
    qDebug() << "\n🧪 Test: Reset du Lion";
    
    // Mettre le lion dans un état non-standard
    testLion->setFaim(0);
    testLion->setSoif(100);
    testLion->setHumeur(25);
    testLion->setEmpoisonnement(50);
    
    // Reset le lion
    testLion->resetAnimal();
    
    // Vérifier que toutes les valeurs sont revenues à la normale
    QCOMPARE(testLion->getFaim(), 50);
    QCOMPARE(testLion->getSoif(), 50);
    QCOMPARE(testLion->getHumeur(), 50);
    QCOMPARE(testLion->getEmpoisonnement(), 0);
    QCOMPARE(testLion->getEstMort(), false);
    
    qDebug() << "✅ Reset du lion fonctionne correctement";
}

// ==================== TESTS DES ALIMENTS ====================

void TestTamaLyon::testAlimentManager()
{
    qDebug() << "\n🧪 Test: AlimentManager";
    
    // Vérifier que tous les aliments sont créés
    int count = testAlimentManager->getAlimentCount();
    qDebug() << "📊 Nombre d'aliments disponibles:" << count;
    
    QVERIFY(count > 0);
    QCOMPARE(count, 7); // Nous avons 7 aliments définis
    
    // Tester l'accès aux aliments
    for (int i = 0; i < count; i++) {
        Aliment* aliment = testAlimentManager->getAlimentByIndex(i);
        QVERIFY(aliment != nullptr);
        QVERIFY(!aliment->getNom().isEmpty());
        qDebug() << "📋" << i << ":" << aliment->getEmoji() << aliment->getNom();
    }
    
    qDebug() << "✅ AlimentManager fonctionne correctement";
}

void TestTamaLyon::testAlimentEffects()
{
    qDebug() << "\n🧪 Test: Effets des aliments";
    
    // Tester chaque aliment
    for (int i = 0; i < testAlimentManager->getAlimentCount(); i++) {
        Aliment* aliment = testAlimentManager->getAlimentByIndex(i);
        
        // Sauvegarder l'état initial
        int faimInitiale = testLion->getFaim();
        int soifInitiale = testLion->getSoif();
        int humeurInitiale = testLion->getHumeur();
        int empoisonnementInitial = testLion->getEmpoisonnement();
        
        // Reset le lion pour avoir un état propre
        testLion->resetAnimal();
        
        qDebug() << "🔬 Test aliment:" << aliment->getNom();
        qDebug() << "   Impact attendu - Faim:" << aliment->getFaimImpact() 
                 << "Soif:" << aliment->getSoifImpact() 
                 << "Humeur:" << aliment->getHumeurImpact()
                 << "Toxique:" << aliment->getEstToxique();
        
        // Appliquer l'aliment
        testLion->donnerAliment(aliment);
        
        qDebug() << "   État résultant - Faim:" << testLion->getFaim()
                 << "Soif:" << testLion->getSoif()
                 << "Humeur:" << testLion->getHumeur()
                 << "Empoisonnement:" << testLion->getEmpoisonnement();
        
        // Vérifier que l'aliment a eu un effet
        bool aEuEffet = (testLion->getFaim() != 50) || 
                       (testLion->getSoif() != 50) || 
                       (testLion->getHumeur() != 50) || 
                       (testLion->getEmpoisonnement() != 0);
        
        QVERIFY(aEuEffet);
    }
    
    qDebug() << "✅ Tous les aliments ont des effets corrects";
}

// ==================== TESTS RÉSEAU ====================

void TestTamaLyon::testServerStart()
{
    qDebug() << "\n🧪 Test: Démarrage du serveur";
    
    QSignalSpy spy(testLionManager, &LionManager::connectionStatusChanged);
    
    // Démarrer en mode host
    testLionManager->startAsHost();
    
    // Attendre que le signal soit émis
    QVERIFY(spy.wait(3000));
    
    // Vérifier que le mode host est activé
    QVERIFY(testLionManager->isHostMode());
    
    qDebug() << "✅ Serveur démarré correctement";
}

void TestTamaLyon::testClientConnection()
{
    qDebug() << "\n🧪 Test: Connexion client";
    
    // Créer un deuxième LionManager pour le client
    LionManager* clientManager = new LionManager(this);
    Lion* clientLion = new Lion("ClientLion", this);
    AlimentManager* clientAlimentManager = new AlimentManager(this);
    
    clientAlimentManager->setLion(clientLion);
    clientAlimentManager->setLionManager(clientManager);
    clientManager->setAlimentManager(clientAlimentManager);
    
    // Démarrer le serveur
    testLionManager->startAsHost();
    
    // Attendre un peu pour que le serveur soit prêt
    QThread::msleep(500);
    
    // Connecter le client
    QSignalSpy spy(clientManager, &LionManager::connectionStatusChanged);
    clientManager->joinAsClient();
    
    // Attendre la connexion
    QVERIFY(spy.wait(3000));
    
    // Vérifier que le client n'est pas en mode host
    QVERIFY(!clientManager->isHostMode());
    
    qDebug() << "✅ Client connecté correctement";
    
    // Nettoyer
    clientManager->deleteLater();
    clientLion->deleteLater();
    clientAlimentManager->deleteLater();
}

void TestTamaLyon::testHostClientBasicSync()
{
    qDebug() << "\n🧪 Test: Synchronisation basique Host-Client";
    
    LionManager* hostManager = nullptr;
    LionManager* clientManager = nullptr;
    
    setupHostClient(hostManager, clientManager);
    
    // Modifier l'état sur l'hôte
    Lion* hostLion = qobject_cast<Lion*>(hostManager->parent()->findChild<Lion*>());
    QVERIFY(hostLion != nullptr);
    
    hostLion->setFaim(75);
    hostLion->setSoif(25);
    hostLion->setHumeur(90);
    
    // Diffuser l'état
    hostManager->broadcastCurrentState();
    
    // Attendre un peu pour la synchronisation
    QThread::msleep(200);
    
    // Vérifier que le client a reçu l'état
    Lion* clientLion = qobject_cast<Lion*>(clientManager->parent()->findChild<Lion*>());
    QVERIFY(clientLion != nullptr);
    
    qDebug() << "📊 Host - Faim:" << hostLion->getFaim() << "Soif:" << hostLion->getSoif() << "Humeur:" << hostLion->getHumeur();
    qDebug() << "📊 Client - Faim:" << clientLion->getFaim() << "Soif:" << clientLion->getSoif() << "Humeur:" << clientLion->getHumeur();
    
    QCOMPARE(clientLion->getFaim(), hostLion->getFaim());
    QCOMPARE(clientLion->getSoif(), hostLion->getSoif());
    QCOMPARE(clientLion->getHumeur(), hostLion->getHumeur());
    
    qDebug() << "✅ Synchronisation basique fonctionne";
    
    // Nettoyer
    hostManager->deleteLater();
    clientManager->deleteLater();
}

void TestTamaLyon::testClientAlimentCommand()
{
    qDebug() << "\n🧪 Test: Commande d'aliment du client";
    
    LionManager* hostManager = nullptr;
    LionManager* clientManager = nullptr;
    
    setupHostClient(hostManager, clientManager);
    
    // Obtenir les lions et alimentManagers
    Lion* hostLion = qobject_cast<Lion*>(hostManager->parent()->findChild<Lion*>());
    Lion* clientLion = qobject_cast<Lion*>(clientManager->parent()->findChild<Lion*>());
    AlimentManager* clientAlimentManager = qobject_cast<AlimentManager*>(clientManager->parent()->findChild<AlimentManager*>());
    
    QVERIFY(hostLion != nullptr);
    QVERIFY(clientLion != nullptr);
    QVERIFY(clientAlimentManager != nullptr);
    
    // État initial
    int faimInitialeHost = hostLion->getFaim();
    int faimInitialeClient = clientLion->getFaim();
    
    qDebug() << "📊 État initial - Host faim:" << faimInitialeHost << "Client faim:" << faimInitialeClient;
    
    // Le client donne un aliment (pomme = index 0)
    clientAlimentManager->nourrirLion(0);
    
    // Attendre la propagation
    QThread::msleep(500);
    
    qDebug() << "📊 État final - Host faim:" << hostLion->getFaim() << "Client faim:" << clientLion->getFaim();
    
    // Vérifier que l'état a changé sur l'hôte ET sur le client
    QVERIFY(hostLion->getFaim() != faimInitialeHost || hostLion->getHumeur() != 50);
    QCOMPARE(clientLion->getFaim(), hostLion->getFaim());
    
    qDebug() << "✅ Commande d'aliment du client fonctionne";
    
    // Nettoyer
    hostManager->deleteLater();
    clientManager->deleteLater();
}

void TestTamaLyon::testHostAuthorityModel()
{
    qDebug() << "\n🧪 Test: Modèle d'autorité du serveur";
    
    LionManager* hostManager = nullptr;
    LionManager* clientManager = nullptr;
    
    setupHostClient(hostManager, clientManager);
    
    // Obtenir les lions
    Lion* hostLion = qobject_cast<Lion*>(hostManager->parent()->findChild<Lion*>());
    Lion* clientLion = qobject_cast<Lion*>(clientManager->parent()->findChild<Lion*>());
    
    QVERIFY(hostLion != nullptr);
    QVERIFY(clientLion != nullptr);
    
    // Synchroniser l'état initial
    hostManager->broadcastCurrentState();
    QThread::msleep(100);
    
    // L'hôte modifie directement son état
    hostLion->setFaim(80);
    hostManager->broadcastCurrentState();
    QThread::msleep(100);
    
    // Le client essaie de modifier directement son état (ne devrait pas persister)
    clientLion->setFaim(20);
    
    // L'hôte diffuse à nouveau son état
    hostManager->broadcastCurrentState();
    QThread::msleep(100);
    
    // Le client devrait avoir l'état de l'hôte, pas son propre état
    qDebug() << "📊 Host faim:" << hostLion->getFaim() << "Client faim:" << clientLion->getFaim();
    QCOMPARE(clientLion->getFaim(), 80); // État de l'hôte
    
    qDebug() << "✅ Modèle d'autorité du serveur fonctionne";
    
    // Nettoyer
    hostManager->deleteLater();
    clientManager->deleteLater();
}

void TestTamaLyon::testMultipleClientsSync()
{
    qDebug() << "\n🧪 Test: Synchronisation multi-clients";
    
    // Créer 1 hôte et 2 clients
    LionManager* hostManager = new LionManager(this);
    LionManager* client1Manager = new LionManager(this);
    LionManager* client2Manager = new LionManager(this);
    
    // Configuration hôte
    Lion* hostLion = new Lion("HostLion", this);
    AlimentManager* hostAlimentManager = new AlimentManager(this);
    hostAlimentManager->setLion(hostLion);
    hostAlimentManager->setLionManager(hostManager);
    hostManager->setAlimentManager(hostAlimentManager);
    
    // Configuration client 1
    Lion* client1Lion = new Lion("Client1Lion", this);
    AlimentManager* client1AlimentManager = new AlimentManager(this);
    client1AlimentManager->setLion(client1Lion);
    client1AlimentManager->setLionManager(client1Manager);
    client1Manager->setAlimentManager(client1AlimentManager);
    
    // Configuration client 2
    Lion* client2Lion = new Lion("Client2Lion", this);
    AlimentManager* client2AlimentManager = new AlimentManager(this);
    client2AlimentManager->setLion(client2Lion);
    client2AlimentManager->setLionManager(client2Manager);
    client2Manager->setAlimentManager(client2AlimentManager);
    
    // Démarrer l'hôte
    hostManager->startAsHost();
    QThread::msleep(200);
    
    // Connecter les clients
    client1Manager->joinAsClient();
    client2Manager->joinAsClient();
    QThread::msleep(500);
    
    // L'hôte modifie son état
    hostLion->setFaim(60);
    hostLion->setSoif(70);
    hostManager->broadcastCurrentState();
    QThread::msleep(200);
    
    // Vérifier que les deux clients ont le même état
    qDebug() << "📊 Host - Faim:" << hostLion->getFaim() << "Soif:" << hostLion->getSoif();
    qDebug() << "📊 Client1 - Faim:" << client1Lion->getFaim() << "Soif:" << client1Lion->getSoif();
    qDebug() << "📊 Client2 - Faim:" << client2Lion->getFaim() << "Soif:" << client2Lion->getSoif();
    
    QCOMPARE(client1Lion->getFaim(), hostLion->getFaim());
    QCOMPARE(client1Lion->getSoif(), hostLion->getSoif());
    QCOMPARE(client2Lion->getFaim(), hostLion->getFaim());
    QCOMPARE(client2Lion->getSoif(), hostLion->getSoif());
    
    qDebug() << "✅ Synchronisation multi-clients fonctionne";
    
    // Nettoyer
    hostManager->deleteLater();
    client1Manager->deleteLater();
    client2Manager->deleteLater();
    hostLion->deleteLater();
    client1Lion->deleteLater();
    client2Lion->deleteLater();
}

void TestTamaLyon::testFullNetworkScenario()
{
    qDebug() << "\n🧪 Test: Scénario réseau complet";
    
    LionManager* hostManager = nullptr;
    LionManager* clientManager = nullptr;
    
    setupHostClient(hostManager, clientManager);
    
    // Obtenir les composants
    Lion* hostLion = qobject_cast<Lion*>(hostManager->parent()->findChild<Lion*>());
    Lion* clientLion = qobject_cast<Lion*>(clientManager->parent()->findChild<Lion*>());
    AlimentManager* clientAlimentManager = qobject_cast<AlimentManager*>(clientManager->parent()->findChild<AlimentManager*>());
    
    // Scénario: Le client donne plusieurs aliments
    qDebug() << "🎯 Scénario: Client donne Pomme (index 0)";
    clientAlimentManager->nourrirLion(0); // Pomme
    QThread::msleep(200);
    
    int faimApres1 = hostLion->getFaim();
    qDebug() << "📊 Après pomme - Host faim:" << faimApres1 << "Client faim:" << clientLion->getFaim();
    QCOMPARE(clientLion->getFaim(), faimApres1);
    
    qDebug() << "🎯 Scénario: Client donne Eau (index 2)";
    clientAlimentManager->nourrirLion(2); // Eau
    QThread::msleep(200);
    
    int soifApres2 = hostLion->getSoif();
    qDebug() << "📊 Après eau - Host soif:" << soifApres2 << "Client soif:" << clientLion->getSoif();
    QCOMPARE(clientLion->getSoif(), soifApres2);
    
    qDebug() << "🎯 Scénario: Client donne Champignon toxique (index 4)";
    clientAlimentManager->nourrirLion(4); // ChampignonToxique
    QThread::msleep(200);
    
    int empoisonnementApres3 = hostLion->getEmpoisonnement();
    qDebug() << "📊 Après champignon - Host empoisonnement:" << empoisonnementApres3 << "Client empoisonnement:" << clientLion->getEmpoisonnement();
    QCOMPARE(clientLion->getEmpoisonnement(), empoisonnementApres3);
    
    // Vérifier que les changements sont cohérents
    QVERIFY(faimApres1 > 50); // La pomme augmente la faim
    QVERIFY(soifApres2 > 50); // L'eau augmente la soif
    QVERIFY(empoisonnementApres3 > 0); // Le champignon empoisonne
    
    qDebug() << "✅ Scénario réseau complet réussi";
    
    // Nettoyer
    hostManager->deleteLater();
    clientManager->deleteLater();
}

void TestTamaLyon::testNetworkResilience()
{
    qDebug() << "\n🧪 Test: Résilience réseau";
    
    // Ce test vérifie que le système gère bien les cas d'erreur
    LionManager* testManager = new LionManager(this);
    
    // Tenter de se connecter à un serveur inexistant
    testManager->joinAsClient();
    
    // Le système ne devrait pas crasher
    QVERIFY(true); // Si on arrive ici, pas de crash
    
    qDebug() << "✅ Système résistant aux erreurs réseau";
    
    testManager->deleteLater();
}

// ==================== HELPERS ====================

void TestTamaLyon::waitForSignal(QObject* sender, const char* signal, int timeout)
{
    QSignalSpy spy(sender, signal);
    QVERIFY(spy.wait(timeout));
}

void TestTamaLyon::setupHostClient(LionManager*& host, LionManager*& client)
{
    // Créer l'hôte
    host = new LionManager(this);
    Lion* hostLion = new Lion("HostLion", this);
    AlimentManager* hostAlimentManager = new AlimentManager(this);
    hostAlimentManager->setLion(hostLion);
    hostAlimentManager->setLionManager(host);
    host->setAlimentManager(hostAlimentManager);
    
    // Créer le client
    client = new LionManager(this);
    Lion* clientLion = new Lion("ClientLion", this);
    AlimentManager* clientAlimentManager = new AlimentManager(this);
    clientAlimentManager->setLion(clientLion);
    clientAlimentManager->setLionManager(client);
    client->setAlimentManager(clientAlimentManager);
    
    // Démarrer l'hôte
    host->startAsHost();
    QThread::msleep(200);
    
    // Connecter le client
    client->joinAsClient();
    QThread::msleep(300);
}

void TestTamaLyon::verifyLionState(Lion* lion, int expectedHunger, int expectedThirst, int expectedMood)
{
    QCOMPARE(lion->getFaim(), expectedHunger);
    QCOMPARE(lion->getSoif(), expectedThirst);
    QCOMPARE(lion->getHumeur(), expectedMood);
}

// Point d'entrée pour les tests
QTEST_MAIN(TestTamaLyon)
#include "TestTamaLyon.moc"
