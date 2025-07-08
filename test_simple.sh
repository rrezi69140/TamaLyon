#!/bin/bash

echo "🧪 === TEST SIMPLE DE SYNCHRONISATION ==="
echo "========================================"
echo ""

cd "$(dirname "$0")"

# Tuer les processus existants
pkill -f TamaLyon 2>/dev/null
sleep 1

# Compiler le projet
echo "🔨 Compilation..."
make clean && make

if [ $? -ne 0 ]; then
    echo "❌ Erreur de compilation"
    exit 1
fi

echo ""
echo "🚀 Test automatisé de synchronisation"
echo "====================================="

# Créer un script AppleScript pour automatiser les clics
cat > test_automation.scpt << 'EOF'
tell application "TamaLyon"
    activate
end tell

delay 2

-- Cliquer sur le bouton "Héberger" (premier bouton)
tell application "System Events"
    tell process "TamaLyon"
        click button "🏠 Héberger" of window 1
    end tell
end tell

delay 1
EOF

# Lancer la première instance (hôte)
echo "1️⃣  Lancement de l'hôte..."
./TamaLyon.app/Contents/MacOS/TamaLyon > host_test.log 2>&1 &
HOST_PID=$!

sleep 3

# Utiliser AppleScript pour cliquer sur "Héberger"
echo "🏠 Activation du mode hôte..."
osascript test_automation.scpt 2>/dev/null

sleep 2

# Lancer la deuxième instance (client)
echo "2️⃣  Lancement du client..."
./TamaLyon.app/Contents/MacOS/TamaLyon > client_test.log 2>&1 &
CLIENT_PID=$!

sleep 3

# Créer un script pour le client
cat > client_automation.scpt << 'EOF'
tell application "System Events"
    tell process "TamaLyon"
        -- Trouver la fenêtre qui n'est pas l'hôte
        set clientWindow to window 2
        click button "🔗 Rejoindre" of clientWindow
    end tell
end tell

delay 2

-- Simuler un drag & drop (difficile avec AppleScript, on va juste cliquer)
tell application "System Events"
    tell process "TamaLyon"
        set clientWindow to window 2
        -- Cliquer sur un aliment puis sur la zone du lion
        click at {150, 300} of clientWindow
        delay 0.5
        click at {500, 400} of clientWindow
    end tell
end tell
EOF

echo "🔗 Connexion du client..."
osascript client_automation.scpt 2>/dev/null

# Attendre et observer
echo "⏱️  Observation pendant 10 secondes..."
sleep 10

# Analyser les logs
echo ""
echo "📊 ANALYSE DES RÉSULTATS"
echo "========================"

echo ""
echo "🏠 LOGS DE L'HÔTE:"
echo "-----------------"
if [ -f "host_test.log" ]; then
    echo "Démarrage serveur:"
    grep -i "serveur\|server\|host" host_test.log | head -3
    
    echo ""
    echo "Connexions clients:"
    grep -i "client.*connecté\|new.*connection" host_test.log | head -3
    
    echo ""
    echo "Commandes reçues:"
    grep -i "commande.*reçue\|command.*received" host_test.log | head -3
    
    echo ""
    echo "Changements d'état:"
    grep -i "état.*après\|faim\|soif" host_test.log | tail -3
else
    echo "❌ Pas de logs hôte"
fi

echo ""
echo "🔗 LOGS DU CLIENT:"
echo "-----------------"
if [ -f "client_test.log" ]; then
    echo "Connexion:"
    grep -i "connecté\|connected\|client" client_test.log | head -3
    
    echo ""
    echo "Commandes envoyées:"
    grep -i "envoi\|send.*command" client_test.log | head -3
    
    echo ""
    echo "États reçus:"
    grep -i "état.*reçu\|state.*received" client_test.log | head -3
else
    echo "❌ Pas de logs client"
fi

# Diagnostic
echo ""
echo "🔍 DIAGNOSTIC:"
echo "============="

ISSUES=0

# Vérifier le serveur
if grep -q "serveur.*démarré\|server.*start" host_test.log 2>/dev/null; then
    echo "✅ Serveur démarré"
else
    echo "❌ Serveur non démarré"
    ISSUES=$((ISSUES + 1))
fi

# Vérifier la connexion client
if grep -q "connecté\|connected" client_test.log 2>/dev/null; then
    echo "✅ Client connecté"
else
    echo "❌ Client non connecté"
    ISSUES=$((ISSUES + 1))
fi

# Vérifier les commandes
if grep -q "commande.*reçue" host_test.log 2>/dev/null; then
    echo "✅ Commandes transmises"
else
    echo "⚠️  Pas de commandes détectées"
    ISSUES=$((ISSUES + 1))
fi

# Nettoyer
kill $HOST_PID $CLIENT_PID 2>/dev/null
rm -f test_automation.scpt client_automation.scpt

echo ""
if [ $ISSUES -eq 0 ]; then
    echo "✅ SYSTÈME FONCTIONNEL"
else
    echo "❌ $ISSUES PROBLÈME(S) DÉTECTÉ(S)"
    echo ""
    echo "💡 Consultez les logs:"
    echo "   cat host_test.log"
    echo "   cat client_test.log"
fi

echo ""
echo "🧪 === FIN DU TEST ==="
