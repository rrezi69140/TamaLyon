#!/bin/bash

echo "🔍 Test de synchronisation - Surveillance des logs"
echo "=================================================="
echo ""
echo "1. Tuez toutes les instances existantes..."
pkill -f TamaLyon

echo "2. Construction du projet..."
make clean && make

if [ $? -ne 0 ]; then
    echo "❌ Erreur de compilation"
    exit 1
fi

echo ""
echo "3. Lancement de l'hôte (terminal 1)..."
echo "   - Cliquez sur 'Héberger' dans l'interface"
echo "   - Puis testez le drag & drop d'un aliment"
echo ""

# Lancer l'hôte avec logs détaillés
QT_LOGGING_RULES="*=true" ./TamaLyon.app/Contents/MacOS/TamaLyon &
HOST_PID=$!

echo "4. Attendez quelques secondes, puis lancez le client..."
sleep 3

echo ""
echo "5. Lancement du client (terminal 2)..."
echo "   - Cliquez sur 'Rejoindre' dans l'interface"
echo "   - Puis testez le drag & drop d'un aliment"
echo ""

# Lancer le client avec logs détaillés
QT_LOGGING_RULES="*=true" ./TamaLyon.app/Contents/MacOS/TamaLyon &
CLIENT_PID=$!

echo ""
echo "🎯 INSTRUCTIONS DE TEST:"
echo "========================"
echo "1. Sur l'HÔTE: Cliquez 'Héberger'"
echo "2. Sur le CLIENT: Cliquez 'Rejoindre'" 
echo "3. Sur le CLIENT: Faites glisser un aliment sur le lion"
echo "4. Observez si l'état change sur les DEUX instances"
echo ""
echo "💡 Pour arrêter le test: Ctrl+C"
echo ""

# Attendre que l'utilisateur arrête le test
wait $HOST_PID $CLIENT_PID
