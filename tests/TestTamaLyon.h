#ifndef TESTTAMALYON_H
#define TESTTAMALYON_H

#include <QtTest/QtTest>
#include <QObject>
#include <QSignalSpy>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>

// Inclure les classes à tester
#include "../Lion.h"
#include "../AlimentManager.h"
#include "../LionManager.h"
#include "../WebSocketServer.h"
#include "../WebSocketClient.h"
#include "../AlimentsConcrets.h"

/**
 * @brief Tests unitaires pour TamaLyon
 * 
 * Ces tests vérifient :
 * 1. La logique métier (Lion, Aliments, effets)
 * 2. La synchronisation réseau (Host/Client)
 * 3. L'intégration complète du système
 */
class TestTamaLyon : public QObject
{
    Q_OBJECT

private slots:
    // Tests de base
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    // Tests de la logique métier
    void testLionCreation();
    void testLionAlimentBasique();
    void testLionAlimentToxique();
    void testLionDecay();
    void testLionMort();
    void testLionReset();

    // Tests des aliments
    void testAlimentManager();
    void testAlimentEffects();

    // Tests réseau - Configuration
    void testServerStart();
    void testClientConnection();

    // Tests réseau - Synchronisation
    void testHostClientBasicSync();
    void testClientAlimentCommand();
    void testHostAuthorityModel();
    void testMultipleClientsSync();

    // Tests d'intégration complète
    void testFullNetworkScenario();
    void testNetworkResilience();

private:
    // Helpers de test
    void waitForSignal(QObject* sender, const char* signal, int timeout = 5000);
    void setupHostClient(LionManager*& host, LionManager*& client);
    void verifyLionState(Lion* lion, int expectedHunger, int expectedThirst, int expectedMood);
    
    // Objets de test
    Lion* testLion;
    AlimentManager* testAlimentManager;
    LionManager* testLionManager;
};

#endif // TESTTAMALYON_H
