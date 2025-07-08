# 📁 Organisation des Fichiers TamaLyon

## 🗂️ Structure des Répertoires

```
TamaLyon/
├── 📁 logs/                    # Fichiers de logs
│   ├── 📄 application.log      # Logs de l'application
│   ├── 📄 network.log          # Logs réseau
│   └── 📄 debug.log            # Logs de debug
├── 📁 temp/                    # Fichiers temporaires
│   ├── 📄 *.tmp                # Fichiers temporaires
│   └── 📄 *.cache              # Cache temporaire
├── 📁 build/                   # Fichiers de compilation
│   ├── 📁 moc/                 # Fichiers MOC générés
│   ├── 📁 obj/                 # Fichiers objets (.o)
│   ├── 📁 rcc/                 # Ressources compilées
│   └── 📁 ui/                  # Interfaces utilisateur compilées
└── 📁 scripts/                 # Scripts d'automatisation
    ├── 📜 organize_project.sh  # Organisation du projet
    ├── 📜 clean_project.sh     # Nettoyage complet
    └── 📜 monitor_logs.sh      # Surveillance des logs
```

## 🚀 Scripts Disponibles

### 🗂️ `organize_project.sh`
Organise automatiquement le projet en déplaçant les fichiers dans les bons répertoires :
```bash
./scripts/organize_project.sh
```

**Fonctions :**
- ✅ Crée les dossiers nécessaires
- 📋 Déplace les logs vers `logs/`
- 🧹 Nettoie les fichiers temporaires
- 📦 Organise les fichiers de build

### 🧹 `clean_project.sh`
Nettoie complètement le projet :
```bash
./scripts/clean_project.sh
```

**Fonctions :**
- 🔨 Supprime les fichiers de build
- 🗑️ Efface les applications compilées
- ⚙️ Nettoie les fichiers temporaires Qt
- 👤 Supprime les fichiers utilisateur
- 🖥️ Efface les fichiers système (.DS_Store, etc.)

### 📡 `monitor_logs.sh`
Surveille les logs en temps réel avec coloration :
```bash
./scripts/monitor_logs.sh
```

**Fonctionnalités :**
- 🎨 Coloration automatique des logs
- 📡 Surveillance en temps réel
- 🔍 Détection automatique des nouveaux fichiers
- ⏹️ Arrêt avec Ctrl+C

## 🎨 Coloration des Logs

| Type de Log | Couleur | Exemple |
|-------------|---------|---------|
| 🔴 ERROR    | Rouge   | `[ERROR] Connexion échouée` |
| 🟡 WARNING  | Jaune   | `[WARN] Mémoire faible` |
| 🔵 INFO     | Cyan    | `[INFO] Application démarrée` |
| ⚪ DEBUG    | Gris    | `[DEBUG] Variable x = 42` |
| 🟢 SUCCESS  | Vert    | `[SUCCESS] ✅ Connexion établie` |
| 🟣 LION     | Magenta | `🦁 Lion créé: "Simba"` |
| 🟨 ALIMENTS | Jaune clair | `🍕 Pizza donnée au lion` |

## 📋 Maintenance Régulière

### Quotidienne
```bash
# Organiser le projet
./scripts/organize_project.sh
```

### Hebdomadaire
```bash
# Nettoyage complet
./scripts/clean_project.sh
```

### Pour le Debug
```bash
# Surveillance des logs en direct
./scripts/monitor_logs.sh &

# Lancer l'application
./TamaLyon.app/Contents/MacOS/TamaLyon
```

## 🔧 Configuration

### Variables d'Environnement
```bash
export TAMALYON_LOG_LEVEL=DEBUG    # Niveau de log (DEBUG, INFO, WARN, ERROR)
export TAMALYON_LOG_DIR=logs       # Répertoire des logs
export TAMALYON_TEMP_DIR=temp      # Répertoire temporaire
```

### Fichiers de Configuration
- `.gitignore` : Ignore automatiquement tous les fichiers temporaires
- `*.pro` : Configuration qmake mise à jour pour la nouvelle structure
- `CMakeLists.txt` : Configuration CMake avec les nouveaux chemins

## 🚨 Résolution des Problèmes

### Problème : Fichiers temporaires dans le répertoire racine
**Solution :**
```bash
./scripts/organize_project.sh
```

### Problème : Build corrompu
**Solution :**
```bash
./scripts/clean_project.sh
qmake TamaLyon.pro
make
```

### Problème : Logs illisibles
**Solution :**
```bash
./scripts/monitor_logs.sh
```

## 📝 Conventions

### Nommage des Logs
- `application_YYYYMMDD_HHMMSS.log` : Logs principaux
- `network_YYYYMMDD_HHMMSS.log` : Logs réseau
- `debug_YYYYMMDD_HHMMSS.log` : Logs de debug

### Nommage des Fichiers Temporaires
- `*.tmp` : Fichiers temporaires généraux
- `*.cache` : Fichiers de cache
- `*.lock` : Fichiers de verrouillage

Cette organisation garantit un projet propre, maintenable et facile à déboguer ! 🎯
