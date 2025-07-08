#!/bin/bash

echo "🧪 === DIAGNOSTIC RAPIDE TAMALYON ==="
echo "==================================="
echo ""

cd "$(dirname "$0")"

# Nettoyer les processus existants
pkill -f TamaLyon 2>/dev/null

# Compiler
echo "🔨 Compilation..."
rm -f Makefile
/Users/rachidrezig/Qt/6.9.1/macos/bin/qmake TamaLyon.pro && make

if [ $? -ne 0 ]; then
    echo "❌ Erreur de compilation"
    exit 1
fi

echo ""
echo "🔍 TESTS MANUELS GUIDÉS"
echo "======================="

echo ""
echo "📋 ÉTAPES À SUIVRE :"
echo "1. Je vais lancer 2 instances de TamaLyon"
echo "2. Vous devrez :"
echo "   - Sur la 1ère fenêtre : Cliquer 'Héberger'"
echo "   - Sur la 2ème fenêtre : Cliquer 'Rejoindre'"
echo "   - Sur la 2ème fenêtre : Faire glisser un aliment sur le lion"
echo "3. Observez si l'état change sur LES DEUX fenêtres"
echo ""

read -p "📝 Appuyez sur Entrée pour lancer les instances..."

echo ""
echo "🏠 Lancement instance 1 (HÔTE)..."
./TamaLyon.app/Contents/MacOS/TamaLyon > logs_host_manual.log 2>&1 &
HOST_PID=$!

sleep 2

echo "🔗 Lancement instance 2 (CLIENT)..."
./TamaLyon.app/Contents/MacOS/TamaLyon > logs_client_manual.log 2>&1 &
CLIENT_PID=$!

echo ""
echo "✅ Deux instances lancées !"
echo ""
echo "📌 MAINTENANT, SUIVEZ CES ÉTAPES :"
echo ""
echo "1️⃣  Sur la PREMIÈRE fenêtre TamaLyon :"
echo "    → Cliquez sur le bouton '🏠 Héberger'"
echo ""
echo "2️⃣  Sur la DEUXIÈME fenêtre TamaLyon :"
echo "    → Cliquez sur le bouton '🔗 Rejoindre'"
echo ""
echo "3️⃣  Sur la DEUXIÈME fenêtre TamaLyon :"
echo "    → Faites glisser UN aliment (ex: pomme) sur le lion"
echo ""
echo "4️⃣  OBSERVEZ :"
echo "    → Est-ce que les barres de statistiques changent sur les DEUX fenêtres ?"
echo "    → Est-ce que l'image du lion change sur les DEUX fenêtres ?"
echo ""

# Attendre que l'utilisateur teste
echo "⏱️  Prenez le temps de tester (60 secondes max)..."
echo "    Appuyez sur Ctrl+C quand vous avez fini de tester"

# Fonction pour gérer l'interruption
cleanup() {
    echo ""
    echo "🔍 ANALYSE DES LOGS..."
    
    echo ""
    echo "📊 LOGS DE L'HÔTE :"
    echo "=================="
    if [ -f "logs_host_manual.log" ]; then
        echo ""
        echo "🏠 Messages de serveur :"
        grep -i "serveur\|server\|host\|héberg" logs_host_manual.log | head -5
        
        echo ""
        echo "📡 Connexions reçues :"
        grep -i "client.*connecté\|new.*connection" logs_host_manual.log | head -3
        
        echo ""
        echo "📥 Commandes reçues :"
        grep -i "commande.*reçue\|command.*received\|aliment.*reçu" logs_host_manual.log | head -3
        
        echo ""
        echo "📈 Changements d'état :"
        grep -i "faim.*après\|soif.*après\|état.*après" logs_host_manual.log | head -3
    else
        echo "❌ Pas de logs hôte trouvés"
    fi
    
    echo ""
    echo "📊 LOGS DU CLIENT :"
    echo "=================="
    if [ -f "logs_client_manual.log" ]; then
        echo ""
        echo "🔗 Connexion :"
        grep -i "connecté\|connected\|client.*join" logs_client_manual.log | head -3
        
        echo ""
        echo "📤 Commandes envoyées :"
        grep -i "envoi.*commande\|send.*command\|nourrissage" logs_client_manual.log | head -3
        
        echo ""
        echo "📥 États reçus :"
        grep -i "état.*reçu\|state.*received" logs_client_manual.log | head -3
    else
        echo "❌ Pas de logs client trouvés"
    fi
    
    # Arrêter les processus
    kill $HOST_PID $CLIENT_PID 2>/dev/null
    
    echo ""
    echo "🎯 QUESTIONS DE DIAGNOSTIC :"
    echo "============================"
    echo ""
    echo "❓ Est-ce que l'hôte a bien démarré le serveur ?"
    if grep -q "serveur.*démarré\|server.*start" logs_host_manual.log 2>/dev/null; then
        echo "✅ OUI - Serveur démarré"
    else
        echo "❌ NON - Serveur non démarré"
    fi
    
    echo ""
    echo "❓ Est-ce que le client s'est connecté ?"
    if grep -q "connecté\|connected" logs_client_manual.log 2>/dev/null; then
        echo "✅ OUI - Client connecté"
    else
        echo "❌ NON - Client non connecté"
    fi
    
    echo ""
    echo "❓ Est-ce que le client envoie des commandes d'aliment ?"
    if grep -q "nourrissage\|aliment.*index\|command.*sent" logs_client_manual.log 2>/dev/null; then
        echo "✅ OUI - Commandes envoyées"
    else
        echo "❌ NON - Pas de commandes détectées"
    fi
    
    echo ""
    echo "❓ Est-ce que l'hôte reçoit les commandes ?"
    if grep -q "commande.*reçue\|command.*received" logs_host_manual.log 2>/dev/null; then
        echo "✅ OUI - Commandes reçues par l'hôte"
    else
        echo "❌ NON - Hôte ne reçoit pas les commandes"
    fi
    
    echo ""
    echo "💡 FICHIERS DE LOG COMPLETS :"
    echo "   - logs_host_manual.log (hôte)"
    echo "   - logs_client_manual.log (client)"
    echo ""
    echo "🔍 Pour voir tous les logs : cat logs_host_manual.log"
    echo "🔍 Pour voir tous les logs : cat logs_client_manual.log"
    
    exit 0
}

# Capturer Ctrl+C
trap cleanup INT

# Attendre maximum 60 secondes
sleep 60

# Si pas d'interruption, faire le cleanup
cleanup
