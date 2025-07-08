#!/bin/bash

# Test spécifique pour les commandes d'aliment et synchronisation réseau
# Avec correction de l'inversion des rôles

echo "🧪 === TEST ALIMENT & SYNCHRONISATION RÉSEAU ==="
echo "📅 Date: $(date)"
echo ""

# Nettoyer les anciens logs
rm -f logs_host_corrected.log logs_client_corrected.log

echo "🚀 1. Lancement de l'instance HOST (qui doit cliquer sur 'Héberger')"
./TamaLyon.app/Contents/MacOS/TamaLyon > logs_host_corrected.log 2>&1 &
HOST_PID=$!

sleep 3

echo "🔗 2. Lancement de l'instance CLIENT (qui doit cliquer sur 'Rejoindre')"
./TamaLyon.app/Contents/MacOS/TamaLyon > logs_client_corrected.log 2>&1 &
CLIENT_PID=$!

echo ""
echo "⚠️  IMPORTANT: Instructions pour l'utilisateur ⚠️"
echo "1. 🏠 Dans la PREMIÈRE fenêtre: Cliquer sur 'Héberger'"
echo "2. 🔗 Dans la DEUXIÈME fenêtre: Cliquer sur 'Rejoindre'"
echo "3. 🍎 Dans la fenêtre CLIENT: Faire un drag & drop d'un aliment sur le lion"
echo "4. ⏰ Attendre 5 secondes puis presser ENTRÉE pour analyser"
echo ""
read -p "Pressez ENTRÉE quand vous avez terminé le test..."

# Arrêter les processus
echo "🛑 Arrêt des processus..."
kill $HOST_PID 2>/dev/null
kill $CLIENT_PID 2>/dev/null
sleep 2

echo ""
echo "📊 === ANALYSE DES LOGS ==="

# Vérifier le serveur
echo "🏠 HOST:"
if grep -q "Serveur WebSocket démarré" logs_host_corrected.log; then
    echo "  ✅ Serveur démarré"
else
    echo "  ❌ Serveur non démarré"
fi

if grep -q "Client connecté" logs_host_corrected.log; then
    echo "  ✅ Client connecté"
else
    echo "  ❌ Aucun client connecté"
fi

if grep -q "commande reçue" logs_host_corrected.log; then
    echo "  ✅ Commandes reçues du client"
    grep "commande reçue" logs_host_corrected.log | head -3
else
    echo "  ❌ Aucune commande reçue du client"
fi

if grep -q "État diffusé" logs_host_corrected.log; then
    echo "  ✅ États diffusés aux clients"
else
    echo "  ❌ Aucun état diffusé"
fi

echo ""
echo "📱 CLIENT:"
if grep -q "connecté avec succès" logs_client_corrected.log; then
    echo "  ✅ Connecté au serveur"
else
    echo "  ❌ Non connecté au serveur"
fi

if grep -q "Appel alimentManager.nourrirLion" logs_client_corrected.log; then
    echo "  ✅ Commandes d'aliment envoyées"
    grep "Appel alimentManager.nourrirLion" logs_client_corrected.log | head -3
else
    echo "  ❌ Aucune commande d'aliment envoyée"
fi

if grep -q "État reçu du serveur" logs_client_corrected.log; then
    echo "  ✅ États reçus du serveur"
else
    echo "  ❌ Aucun état reçu du serveur"
fi

echo ""
echo "🔄 SYNCHRONISATION:"

# Vérifier les effets d'aliment
if grep -q "nourrirLion.*CLIENT" logs_client_corrected.log; then
    echo "  ✅ Client envoie les commandes au serveur"
else
    echo "  ❌ Client n'envoie pas les commandes au serveur"
fi

if grep -q "processClientAlimentCommand" logs_host_corrected.log; then
    echo "  ✅ Host traite les commandes du client"
else
    echo "  ❌ Host ne traite pas les commandes du client"
fi

# Vérifier les changements d'état
echo ""
echo "📈 CHANGEMENTS D'ÉTAT:"
echo "Host:"
grep "Hunger\|Thirst\|Affection" logs_host_corrected.log | tail -5 2>/dev/null || echo "  Aucun changement détecté"

echo "Client:"
grep "Hunger\|Thirst\|Affection" logs_client_corrected.log | tail -5 2>/dev/null || echo "  Aucun changement détecté"

echo ""
echo "📁 Logs complets sauvegardés: logs_host_corrected.log et logs_client_corrected.log"
echo "🧪 Test terminé!"
