#!/bin/bash
# monitor_logs.sh - Script de surveillance des logs TamaLyon en temps réel

LOG_DIR="logs"
TEMP_DIR="temp"

echo "📡 Surveillance des logs TamaLyon en temps réel"
echo "==============================================="
echo "📁 Répertoire surveillé: $LOG_DIR/"
echo "⏹️  Appuyez sur Ctrl+C pour arrêter"
echo ""

# Créer les répertoires s'ils n'existent pas
mkdir -p "$LOG_DIR"
mkdir -p "$TEMP_DIR"

# Fonction pour afficher les logs avec couleurs
show_log() {
    local file="$1"
    local name=$(basename "$file" .log)
    
    echo "📋 ===== $name ====="
    
    # Colorer les logs selon leur type
    tail -f "$file" | while read line; do
        case "$line" in
            *"ERROR"*|*"ERREUR"*) echo -e "\033[31m$line\033[0m" ;;  # Rouge
            *"WARN"*|*"WARNING"*) echo -e "\033[33m$line\033[0m" ;;   # Jaune
            *"INFO"*) echo -e "\033[36m$line\033[0m" ;;               # Cyan
            *"DEBUG"*) echo -e "\033[90m$line\033[0m" ;;              # Gris
            *"SUCCESS"*|*"✅"*) echo -e "\033[32m$line\033[0m" ;;     # Vert
            *"🦁"*) echo -e "\033[35m$line\033[0m" ;;                 # Magenta
            *"🍕"*|*"🍎"*|*"💧"*) echo -e "\033[93m$line\033[0m" ;;   # Jaune clair
            *) echo "$line" ;;
        esac
    done &
}

# Surveiller les fichiers de logs existants
for logfile in "$LOG_DIR"/*.log; do
    if [[ -f "$logfile" ]]; then
        show_log "$logfile"
    fi
done

# Surveiller les nouveaux fichiers de logs
echo "🔍 En attente de nouveaux logs..."

# Utiliser fswatch si disponible, sinon surveiller manuellement
if command -v fswatch > /dev/null; then
    fswatch -o "$LOG_DIR" | while read f; do
        for logfile in "$LOG_DIR"/*.log; do
            if [[ -f "$logfile" ]] && [[ ! -f "$TEMP_DIR/$(basename $logfile).watched" ]]; then
                touch "$TEMP_DIR/$(basename $logfile).watched"
                show_log "$logfile"
            fi
        done
    done
else
    # Surveillance manuelle
    while true; do
        for logfile in "$LOG_DIR"/*.log; do
            if [[ -f "$logfile" ]] && [[ ! -f "$TEMP_DIR/$(basename $logfile).watched" ]]; then
                touch "$TEMP_DIR/$(basename $logfile).watched"
                show_log "$logfile"
            fi
        done
        sleep 1
    done
fi
