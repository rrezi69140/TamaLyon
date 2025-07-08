#!/bin/bash
# organize_project.sh - Script pour organiser le projet TamaLyon

echo "🗂️  Organisation du projet TamaLyon..."

# Créer les dossiers s'ils n'existent pas
mkdir -p logs
mkdir -p temp
mkdir -p build/moc
mkdir -p build/obj
mkdir -p build/rcc
mkdir -p build/ui

# Déplacer les logs existants
echo "📋 Déplacement des logs..."
find . -maxdepth 1 -name "logs_*.log" -exec mv {} logs/ \; 2>/dev/null || true
find . -maxdepth 1 -name "*.log" -exec mv {} logs/ \; 2>/dev/null || true

# Nettoyer les fichiers temporaires dans le répertoire racine
echo "🧹 Nettoyage des fichiers temporaires..."
rm -f qrc_qml.cpp 2>/dev/null || true
rm -f moc_*.cpp 2>/dev/null || true
rm -f *.o 2>/dev/null || true

# Déplacer les fichiers temporaires vers les bons dossiers
echo "📦 Organisation des fichiers de build..."
find . -maxdepth 1 -name "moc_*.cpp" -exec mv {} build/moc/ \; 2>/dev/null || true
find . -maxdepth 1 -name "*.o" -exec mv {} build/obj/ \; 2>/dev/null || true

# Afficher le statut
echo "✅ Organisation terminée !"
echo ""
echo "📊 Structure des dossiers :"
echo "  📁 logs/     - Fichiers de logs (.log)"
echo "  📁 temp/     - Fichiers temporaires"
echo "  📁 build/    - Fichiers de compilation"
echo "    📁 moc/    - Fichiers MOC générés"
echo "    📁 obj/    - Fichiers objets (.o)"
echo "    📁 rcc/    - Ressources compilées"
echo "    📁 ui/     - Interfaces utilisateur"
echo ""

# Afficher le contenu des dossiers
echo "📋 Contenu actuel :"
echo "Logs : $(ls -1 logs/ 2>/dev/null | wc -l) fichiers"
echo "Temp : $(ls -1 temp/ 2>/dev/null | wc -l) fichiers"
echo "Build: $(find build/ -type f 2>/dev/null | wc -l) fichiers"
