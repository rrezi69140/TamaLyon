#!/bin/bash
# project_status.sh - Affiche l'état du projet TamaLyon

echo "🦁 ===== ÉTAT DU PROJET TAMALYON ====="
echo ""

# Fonction pour compter les fichiers
count_files() {
    if [[ -d "$1" ]]; then
        find "$1" -type f 2>/dev/null | wc -l | tr -d ' '
    else
        echo "0"
    fi
}

# Fonction pour calculer la taille
calc_size() {
    if [[ -d "$1" ]]; then
        du -sh "$1" 2>/dev/null | cut -f1
    else
        echo "0B"
    fi
}

echo "📊 STATISTIQUES GÉNÉRALES"
echo "=========================="
echo "📁 Code Source:"
echo "   ├── C++ Headers: $(find src/ -name "*.h" 2>/dev/null | wc -l | tr -d ' ') fichiers"
echo "   ├── C++ Sources: $(find src/ -name "*.cpp" 2>/dev/null | wc -l | tr -d ' ') fichiers"
echo "   ├── QML Files:   $(find qml/ -name "*.qml" 2>/dev/null | wc -l | tr -d ' ') fichiers"
echo "   └── Resources:   $(find resources/ -type f 2>/dev/null | wc -l | tr -d ' ') fichiers"
echo ""

echo "🗂️ ORGANISATION"
echo "==============="
echo "📋 Logs:        $(count_files logs/) fichiers ($(calc_size logs/))"
echo "🔧 Build:       $(count_files build/) fichiers ($(calc_size build/))"
echo "⏱️ Temp:        $(count_files temp/) fichiers ($(calc_size temp/))"
echo "📚 Docs:        $(count_files docs/) fichiers ($(calc_size docs/))"
echo "🔨 Scripts:     $(count_files scripts/) fichiers"
echo "🧪 Tests:       $(count_files tests/) fichiers"
echo ""

echo "🏗️ ÉTAT DE COMPILATION"
echo "======================"
if [[ -f "TamaLyon.app/Contents/MacOS/TamaLyon" ]]; then
    app_size=$(calc_size TamaLyon.app)
    app_date=$(stat -f "%Sm" -t "%Y-%m-%d %H:%M" TamaLyon.app/Contents/MacOS/TamaLyon 2>/dev/null)
    echo "✅ Application compilée: $app_size (modifiée: $app_date)"
else
    echo "❌ Application non compilée"
fi

if [[ -f "Makefile" ]]; then
    makefile_date=$(stat -f "%Sm" -t "%Y-%m-%d %H:%M" Makefile 2>/dev/null)
    echo "📄 Makefile présent (généré: $makefile_date)"
else
    echo "⚠️  Makefile absent - exécutez 'qmake'"
fi
echo ""

echo "📡 LOGS RÉCENTS"
echo "==============="
if [[ -d "logs" ]] && [[ $(count_files logs/) -gt 0 ]]; then
    echo "📋 Derniers logs:"
    for log in logs/*.log; do
        if [[ -f "$log" ]]; then
            log_name=$(basename "$log")
            log_size=$(calc_size "$log")
            log_lines=$(wc -l < "$log" 2>/dev/null | tr -d ' ')
            log_date=$(stat -f "%Sm" -t "%H:%M" "$log" 2>/dev/null)
            echo "   └── $log_name: $log_lines lignes, $log_size ($log_date)"
        fi
    done
else
    echo "📭 Aucun log disponible"
fi
echo ""

echo "🔧 OUTILS DISPONIBLES"
echo "===================="
echo "🗂️ ./scripts/organize_project.sh  - Organiser le projet"
echo "🧹 ./scripts/clean_project.sh     - Nettoyer le projet"  
echo "📡 ./scripts/monitor_logs.sh      - Surveiller les logs"
echo "📊 ./scripts/project_status.sh    - Afficher cet état"
echo ""

echo "🚀 COMMANDES RAPIDES"
echo "===================="
echo "Compilation:  qmake && make"
echo "Nettoyage:    ./scripts/clean_project.sh"
echo "Organisation: ./scripts/organize_project.sh"
echo "Tests:        ./scripts/run_tests.sh"
echo ""

# Afficher les warnings s'il y en a
warnings=0

if [[ $(find . -maxdepth 1 -name "*.o" 2>/dev/null | wc -l | tr -d ' ') -gt 0 ]]; then
    echo "⚠️ Fichiers .o dans le répertoire racine"
    warnings=$((warnings + 1))
fi

if [[ $(find . -maxdepth 1 -name "moc_*.cpp" 2>/dev/null | wc -l | tr -d ' ') -gt 0 ]]; then
    echo "⚠️ Fichiers MOC dans le répertoire racine"
    warnings=$((warnings + 1))
fi

if [[ $(find . -maxdepth 1 -name "qrc_*.cpp" 2>/dev/null | wc -l | tr -d ' ') -gt 0 ]]; then
    echo "⚠️ Fichiers RCC dans le répertoire racine"
    warnings=$((warnings + 1))
fi

if [[ $warnings -gt 0 ]]; then
    echo ""
    echo "💡 Utilisez './scripts/organize_project.sh' pour nettoyer"
else
    echo "✅ Projet propre et bien organisé !"
fi

echo ""
echo "🎯 Projet TamaLyon - Version organisée et structurée"
