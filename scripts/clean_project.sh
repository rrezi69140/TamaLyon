#!/bin/bash
# clean_project.sh - Script de nettoyage complet du projet TamaLyon

echo "🧹 Nettoyage complet du projet TamaLyon..."

# Fonction pour compter les fichiers supprimés
count_files() {
    find "$1" -type f 2>/dev/null | wc -l
}

# Sauvegarder les statistiques avant nettoyage
echo "📊 État avant nettoyage :"
echo "  Build files: $(count_files build/)"
echo "  Log files: $(count_files logs/)"
echo "  Temp files: $(count_files temp/)"
echo ""

# Nettoyer les fichiers de build
echo "🔨 Nettoyage des fichiers de build..."
make clean 2>/dev/null || true
rm -rf build/moc/*.cpp
rm -rf build/obj/*.o
rm -rf build/rcc/qrc_*.cpp
rm -rf build/ui/ui_*.h

# Nettoyer les applications compilées
echo "🗑️  Suppression des applications compilées..."
rm -rf *.app/
rm -f TamaLyon
rm -f test_unit_aliment
rm -f basic_test

# Nettoyer les fichiers temporaires Qt
echo "⚙️  Nettoyage des fichiers temporaires Qt..."
find . -name "moc_*.cpp" -not -path "./build/*" -delete
find . -name "qrc_*.cpp" -not -path "./build/*" -delete
find . -name "ui_*.h" -not -path "./build/*" -delete
find . -name "*.o" -not -path "./build/*" -delete

# Nettoyer les fichiers de projet utilisateur
echo "👤 Suppression des fichiers utilisateur..."
rm -f *.pro.user*
rm -f *.qmake.stash
rm -f Makefile*

# Option pour nettoyer les logs (avec confirmation)
read -p "🤔 Voulez-vous aussi nettoyer les logs ? (y/N): " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    echo "🗑️  Nettoyage des logs..."
    rm -f logs/*.log
    echo "   ✅ Logs supprimés"
else
    echo "   ⏭️  Logs conservés"
fi

# Nettoyer les fichiers système
echo "🖥️  Nettoyage des fichiers système..."
find . -name ".DS_Store" -delete 2>/dev/null || true
find . -name "._*" -delete 2>/dev/null || true
find . -name "*~" -delete 2>/dev/null || true

# Afficher les statistiques après nettoyage
echo ""
echo "✅ Nettoyage terminé !"
echo "📊 État après nettoyage :"
echo "  Build files: $(count_files build/)"
echo "  Log files: $(count_files logs/)"
echo "  Temp files: $(count_files temp/)"
echo ""
echo "🎯 Projet prêt pour une compilation propre !"
echo "   Utilisez 'make' ou 'qmake && make' pour recompiler"
