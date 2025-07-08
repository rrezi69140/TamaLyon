#!/bin/bash

echo "🔍 === TEST DE DIAGNOSTIC RÉSEAU ==="
echo "===================================="
echo ""

# Aller dans le répertoire principal
cd "$(dirname "$0")"

echo "📁 Répertoire: $(pwd)"
echo ""

# Compiler le projet principal
echo "🔨 Compilation du projet principal..."
make clean && make

if [ $? -ne 0 ]; then
    echo "❌ Erreur de compilation"
    exit 1
fi

echo ""
echo "🚀 DIAGNOSTIC AUTOMATISÉ"
echo "========================"

# Fonction pour tuer les processus TamaLyon
cleanup() {
    echo "🧹 Nettoyage des processus..."
    pkill -f TamaLyon 2>/dev/null
    sleep 1
}

# Nettoyer au début
cleanup

# Fonction pour lancer TamaLyon en arrière-plan avec logs
launch_tamalyon() {
    local mode=$1
    local logfile=$2
    echo "🚀 Lancement TamaLyon en mode $mode..."
    
    # Lancer avec logs détaillés et capture dans un fichier
    QT_LOGGING_RULES="*=true" ./TamaLyon.app/Contents/MacOS/TamaLyon > "$logfile" 2>&1 &
    local pid=$!
    echo "📋 PID: $pid"
    
    # Attendre que l'application soit prête
    sleep 2
    
    return $pid
}

# Fonction pour simuler les actions dans TamaLyon
simulate_actions() {
    local mode=$1
    local delay=$2
    
    echo "⏱️  Attente de ${delay}s pour $mode..."
    sleep $delay
    
    if [ "$mode" = "HOST" ]; then
        echo "🏠 Simulation: Host démarre le serveur"
        # Dans un vrai test, on pourrait utiliser des outils comme xdotool ou AppleScript
        # Pour l'instant, on simule avec des logs
        echo "[SIMULATION] Host clique sur 'Héberger'"
        
    elif [ "$mode" = "CLIENT" ]; then
        echo "🔗 Simulation: Client se connecte"
        echo "[SIMULATION] Client clique sur 'Rejoindre'"
        sleep 2
        echo "🍎 Simulation: Client fait glisser une pomme"
        echo "[SIMULATION] Client drag & drop aliment index 0"
    fi
}

# Créer les fichiers de log
HOST_LOG="diagnostic_host.log"
CLIENT_LOG="diagnostic_client.log"

# Lancer l'hôte
echo "1️⃣  ÉTAPE 1: Lancement de l'hôte"
launch_tamalyon "HOST" "$HOST_LOG"
HOST_PID=$!

# Attendre un peu
sleep 3

# Lancer le client
echo ""
echo "2️⃣  ÉTAPE 2: Lancement du client"
launch_tamalyon "CLIENT" "$CLIENT_LOG"
CLIENT_PID=$!

# Attendre un peu
sleep 3

echo ""
echo "3️⃣  ÉTAPE 3: Simulation des actions"
echo "====================================="

# Simuler les actions (normalement on ferait ça avec des vrais clics)
simulate_actions "HOST" 2
simulate_actions "CLIENT" 3

# Laisser tourner un moment pour voir les interactions
echo ""
echo "4️⃣  ÉTAPE 4: Observation (10 secondes)"
echo "======================================"
sleep 10

# Analyser les logs
echo ""
echo "5️⃣  ÉTAPE 5: Analyse des logs"
echo "============================="

echo ""
echo "🔍 ANALYSE DU HOST ($HOST_LOG):"
echo "------------------------------"
if [ -f "$HOST_LOG" ]; then
    echo "📊 Lignes de log: $(wc -l < "$HOST_LOG")"
    
    echo ""
    echo "🏠 Messages de démarrage host:"
    grep -i "host\|héberg\|server" "$HOST_LOG" | head -5
    
    echo ""
    echo "📡 Messages réseau (serveur):"
    grep -i "websocket\|server\|client\|connect" "$HOST_LOG" | head -5
    
    echo ""
    echo "🍽️  Messages d'aliments:"
    grep -i "aliment\|nourrir\|commande" "$HOST_LOG" | head -5
    
    echo ""
    echo "📈 Changements d'état:"
    grep -i "état\|faim\|soif\|humeur" "$HOST_LOG" | head -5
    
else
    echo "❌ Fichier de log host non trouvé"
fi

echo ""
echo "🔍 ANALYSE DU CLIENT ($CLIENT_LOG):"
echo "-----------------------------------"
if [ -f "$CLIENT_LOG" ]; then
    echo "📊 Lignes de log: $(wc -l < "$CLIENT_LOG")"
    
    echo ""
    echo "🔗 Messages de connexion client:"
    grep -i "client\|rejoind\|connect" "$CLIENT_LOG" | head -5
    
    echo ""
    echo "📤 Commandes envoyées:"
    grep -i "envoi\|command\|send" "$CLIENT_LOG" | head -5
    
    echo ""
    echo "📥 États reçus:"
    grep -i "reçu\|received\|état" "$CLIENT_LOG" | head -5
    
else
    echo "❌ Fichier de log client non trouvé"
fi

# Analyser les problèmes potentiels
echo ""
echo "6️⃣  ÉTAPE 6: Diagnostic des problèmes"
echo "===================================="

PROBLEMS_FOUND=0

# Vérifier si le serveur a démarré
if [ -f "$HOST_LOG" ] && grep -q "serveur.*démarré\|server.*start" "$HOST_LOG"; then
    echo "✅ Serveur démarré correctement"
else
    echo "❌ PROBLÈME: Serveur n'a pas démarré"
    PROBLEMS_FOUND=$((PROBLEMS_FOUND + 1))
fi

# Vérifier si le client s'est connecté
if [ -f "$CLIENT_LOG" ] && grep -q "connecté\|connected" "$CLIENT_LOG"; then
    echo "✅ Client connecté correctement"
else
    echo "❌ PROBLÈME: Client ne s'est pas connecté"
    PROBLEMS_FOUND=$((PROBLEMS_FOUND + 1))
fi

# Vérifier les commandes d'aliments
if [ -f "$CLIENT_LOG" ] && grep -q "commande.*envoyée\|command.*sent" "$CLIENT_LOG"; then
    echo "✅ Client envoie des commandes"
else
    echo "⚠️  ATTENTION: Pas de commandes d'aliment détectées du client"
    PROBLEMS_FOUND=$((PROBLEMS_FOUND + 1))
fi

# Vérifier si l'hôte reçoit les commandes
if [ -f "$HOST_LOG" ] && grep -q "commande.*reçue\|command.*received" "$HOST_LOG"; then
    echo "✅ Hôte reçoit les commandes"
else
    echo "❌ PROBLÈME: Hôte ne reçoit pas les commandes du client"
    PROBLEMS_FOUND=$((PROBLEMS_FOUND + 1))
fi

# Vérifier la synchronisation d'état
if [ -f "$HOST_LOG" ] && [ -f "$CLIENT_LOG" ]; then
    HOST_STATES=$(grep -c "diffusion\|broadcast" "$HOST_LOG")
    CLIENT_STATES=$(grep -c "état.*reçu\|state.*received" "$CLIENT_LOG")
    
    echo "📊 Diffusions host: $HOST_STATES, Réceptions client: $CLIENT_STATES"
    
    if [ $HOST_STATES -gt 0 ] && [ $CLIENT_STATES -gt 0 ]; then
        echo "✅ Synchronisation d'état active"
    else
        echo "❌ PROBLÈME: Pas de synchronisation d'état"
        PROBLEMS_FOUND=$((PROBLEMS_FOUND + 1))
    fi
fi

# Nettoyer
cleanup

echo ""
echo "7️⃣  RÉSUMÉ DU DIAGNOSTIC"
echo "======================="

if [ $PROBLEMS_FOUND -eq 0 ]; then
    echo "✅ SYSTÈME SEMBLE FONCTIONNEL"
    echo "   Tous les composants de base fonctionnent"
    echo "   Le problème pourrait être dans l'interface utilisateur"
else
    echo "❌ $PROBLEMS_FOUND PROBLÈME(S) DÉTECTÉ(S)"
    echo "   Vérifiez les logs ci-dessus pour plus de détails"
fi

echo ""
echo "📋 FICHIERS DE LOG GÉNÉRÉS:"
echo "   - $HOST_LOG (logs de l'hôte)"
echo "   - $CLIENT_LOG (logs du client)"
echo ""
echo "💡 Pour voir les logs complets:"
echo "   cat $HOST_LOG"
echo "   cat $CLIENT_LOG"

echo ""
echo "🔍 === FIN DU DIAGNOSTIC ==="
