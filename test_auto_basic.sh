#!/bin/bash

# Script de test automatisé pour les commandes d'aliment
# Ce script simule les actions utilisateur via QML

echo "🤖 === TEST AUTOMATISÉ ALIMENT ==="
echo "📅 Date: $(date)"
echo ""

# Nettoyer les anciens logs
rm -f logs_auto_host.log logs_auto_client.log

echo "🚀 Lancement des instances..."

# Lancer les deux instances en arrière-plan
./TamaLyon.app/Contents/MacOS/TamaLyon > logs_auto_host.log 2>&1 &
HOST_PID=$!

sleep 2

./TamaLyon.app/Contents/MacOS/TamaLyon > logs_auto_client.log 2>&1 &
CLIENT_PID=$!

sleep 3

echo "🔍 Vérification du lancement..."

# Vérifier que les processus sont actifs
if ps -p $HOST_PID > /dev/null; then
    echo "  ✅ Instance HOST active (PID: $HOST_PID)"
else
    echo "  ❌ Instance HOST échouée"
    exit 1
fi

if ps -p $CLIENT_PID > /dev/null; then
    echo "  ✅ Instance CLIENT active (PID: $CLIENT_PID)"
else
    echo "  ❌ Instance CLIENT échouée"
    kill $HOST_PID 2>/dev/null
    exit 1
fi

echo ""
echo "⏳ Attendre 5 secondes pour l'initialisation..."
sleep 5

echo "📊 Analyse des logs d'initialisation..."

# Vérifier l'initialisation de base
if grep -q "AlimentManager.*Initialisation" logs_auto_host.log && grep -q "AlimentManager.*Initialisation" logs_auto_client.log; then
    echo "  ✅ AlimentManager initialisé dans les deux instances"
else
    echo "  ❌ Problème d'initialisation AlimentManager"
fi

if grep -q "Lion.*créé" logs_auto_host.log && grep -q "Lion.*créé" logs_auto_client.log; then
    echo "  ✅ Lion créé dans les deux instances"
else
    echo "  ❌ Problème de création du Lion"
fi

# NOTE: Pour un test vraiment automatisé, il faudrait :
# 1. Utiliser QML Test framework ou des injections d'événements
# 2. Ou créer des méthodes C++ pour simuler les actions
# 3. Ou utiliser des triggers temporisés dans le code

echo ""
echo "⚠️  LIMITATION: Test automatisé complet nécessiterait:"
echo "   - QML Test framework pour simuler drag&drop"
echo "   - Ou méthodes C++ pour déclencher actions automatiquement"
echo "   - Ou injection d'événements système"
echo ""

echo "📈 État actuel des instances après 5s:"
echo ""
echo "HOST - Dernières lignes:"
tail -5 logs_auto_host.log

echo ""
echo "CLIENT - Dernières lignes:"
tail -5 logs_auto_client.log

echo ""
echo "🛑 Arrêt des instances..."
kill $HOST_PID 2>/dev/null
kill $CLIENT_PID 2>/dev/null
sleep 2

echo "📁 Logs sauvegardés: logs_auto_host.log et logs_auto_client.log"
echo "🤖 Test automatisé terminé!"

echo ""
echo "💡 Pour un test complet, utilisez le script interactif:"
echo "   ./test_aliment_sync.sh"
