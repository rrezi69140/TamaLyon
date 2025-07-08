#!/bin/bash

echo "🧪 === LANCEMENT DES TESTS TAMALYON ==="
echo "======================================="
echo ""

# Aller dans le dossier de tests
cd "$(dirname "$0")/tests"

echo "📁 Répertoire de tests: $(pwd)"
echo ""

# Nettoyer les anciens fichiers de compilation
echo "🧹 Nettoyage des anciens fichiers..."
rm -f TestTamaLyon Makefile *.o moc_*
rm -rf tmp/

# Générer le Makefile avec qmake
echo "🔧 Génération du Makefile..."
/Users/rachidrezig/Qt/6.9.1/macos/bin/qmake tests.pro

if [ $? -ne 0 ]; then
    echo "❌ Erreur lors de la génération du Makefile"
    exit 1
fi

# Compiler les tests
echo "🔨 Compilation des tests..."
make

if [ $? -ne 0 ]; then
    echo "❌ Erreur lors de la compilation des tests"
    exit 1
fi

echo ""
echo "🚀 Lancement des tests..."
echo "========================"

# Lancer les tests avec output détaillé
./TestTamaLyon -v2

RESULT=$?

echo ""
echo "========================"

if [ $RESULT -eq 0 ]; then
    echo "✅ TOUS LES TESTS ONT RÉUSSI !"
else
    echo "❌ CERTAINS TESTS ONT ÉCHOUÉ (code: $RESULT)"
fi

echo "🧪 === FIN DES TESTS ==="

exit $RESULT
