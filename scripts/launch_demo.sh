#!/bin/bash
# launch_demo.sh - Script pour lancer une démo rapide avec deux instances

echo "🦁 ===== LANCEMENT DÉMO TAMALYON ====="
echo ""

# Vérifier que l'application est compilée
if [[ ! -f "TamaLyon.app/Contents/MacOS/TamaLyon" ]]; then
    echo "❌ Application non compilée!"
    echo "🔨 Compilation en cours..."
    make > /dev/null 2>&1
    if [[ $? -ne 0 ]]; then
        echo "❌ Échec de compilation!"
        exit 1
    fi
    echo "✅ Compilation terminée!"
fi

echo "🚀 Lancement de deux instances TamaLyon..."
echo ""
echo "📋 Instructions pour la démo :"
echo "1️⃣  Instance 1 (Host)  : Cliquez sur 'Démarrer Serveur'"
echo "2️⃣  Instance 2 (Client): Cliquez sur 'Se Connecter'"
echo "3️⃣  Testez le drag & drop d'aliments sur l'instance client"
echo "4️⃣  Observez la synchronisation en temps réel"
echo ""

# Lancer la première instance
echo "🖥️  Lancement Instance 1 (Host)..."
./TamaLyon.app/Contents/MacOS/TamaLyon &
INSTANCE1_PID=$!

# Attendre un peu pour que la première instance se lance
sleep 2

# Lancer la deuxième instance  
echo "🖥️  Lancement Instance 2 (Client)..."
./TamaLyon.app/Contents/MacOS/TamaLyon &
INSTANCE2_PID=$!

echo ""
echo "✅ Deux instances lancées !"
echo "   📟 Instance 1 PID: $INSTANCE1_PID"
echo "   📟 Instance 2 PID: $INSTANCE2_PID"
echo ""
echo "🎯 POUR LA DÉMO :"
echo "   🔸 Host (Instance 1)   : Démarrer Serveur → Mode Host actif"
echo "   🔸 Client (Instance 2) : Se Connecter → Connexion au Host"
echo "   🔸 Test Sync : Drag & drop aliments sur le client"
echo ""
echo "⏹️  Pour arrêter : Ctrl+C ou fermez les fenêtres"
echo ""

# Fonction pour nettoyer en cas d'arrêt
cleanup() {
    echo ""
    echo "🛑 Arrêt des instances..."
    kill $INSTANCE1_PID 2>/dev/null || true
    kill $INSTANCE2_PID 2>/dev/null || true
    echo "✅ Démo terminée !"
    exit 0
}

# Capturer Ctrl+C
trap cleanup SIGINT SIGTERM

# Attendre que les processus se terminent
wait $INSTANCE1_PID $INSTANCE2_PID

echo "🏁 Démo terminée naturellement"
