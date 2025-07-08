# Structure du Projet TamaLyon

## Organisation des Dossiers

```
TamaLyon/
├── src/                          # Code source C++
│   ├── core/                     # Logique métier fondamentale
│   │   ├── Animal.h/.cpp         # Classe de base pour les animaux
│   │   ├── Lion.h/.cpp           # Implémentation spécifique du lion
│   │   ├── Aliment.h/.cpp        # Classe de base des aliments
│   │   ├── AlimentsConcrets.h/.cpp # Implémentations d'aliments spécifiques
│   │   └── EffectHandler.h/.cpp  # Gestionnaire des effets
│   ├── managers/                 # Gestionnaires de haut niveau
│   │   ├── LionManager.h/.cpp    # Gestion d'état et réseau du lion
│   │   └── AlimentManager.h/.cpp # Gestion des aliments
│   └── network/                  # Communication réseau
│       ├── WebSocketServer.h/.cpp # Serveur WebSocket
│       └── WebSocketClient.h/.cpp # Client WebSocket
├── qml/                          # Interface utilisateur QML
│   ├── pages/                    # Pages principales
│   │   ├── Main.qml              # Page principale simple
│   │   ├── MainOOP.qml           # Page principale OOP
│   │   └── MainSimple.qml        # Page simple pour tests
│   └── components/               # Composants réutilisables
│       ├── AnimatedLion.qml      # Animation du lion
│       ├── DraggableAliment.qml  # Aliment déplaçable
│       ├── DraggableIcon.qml     # Icône déplaçable
│       ├── MoodBar.qml           # Barre d'humeur
│       └── LyonFace.qml          # Face du lion
├── resources/                    # Ressources statiques
│   ├── background.png            # Image de fond
│   ├── lion_*.png                # Images des différents états du lion
│   └── lion_mange_*.png          # Séquence d'animation de nourrissage
├── docs/                         # Documentation
│   ├── ARCHITECTURE.md           # Architecture du système
│   ├── GUIDE_UTILISATEUR.md      # Guide d'utilisation
│   ├── COMPILATION_GUIDE.md      # Guide de compilation
│   └── *.puml                    # Diagrammes PlantUML
├── scripts/                      # Scripts d'automatisation
│   ├── run_tests.sh              # Exécution des tests
│   ├── test_sync.sh              # Test de synchronisation
│   └── diagnostic_*.sh           # Scripts de diagnostic
├── tests/                        # Tests unitaires et d'intégration
│   ├── TestTamaLyon.h/.cpp       # Suite de tests principale
│   └── tests.pro                 # Configuration qmake pour tests
├── build/                        # Fichiers de compilation temporaires
│   ├── moc/                      # Fichiers MOC générés
│   ├── obj/                      # Fichiers objets
│   └── rcc/                      # Ressources compilées
├── main.cpp                      # Point d'entrée principal
├── TamaLyon.pro                  # Configuration qmake
├── CMakeLists.txt               # Configuration CMake
└── qml.qrc                      # Fichier de ressources QML
```

## Avantages de cette Structure

### 🏗️ **Modularité**
- **Séparation claire** entre logique métier (`core`), gestion (`managers`) et réseau (`network`)
- **Composants QML réutilisables** dans le dossier `components`
- **Pages distinctes** pour différents modes d'utilisation

### 🔧 **Maintenabilité**
- **Localisation facile** des fichiers par fonction
- **Réduction des dépendances** entre modules
- **Tests isolés** par composant

### 🚀 **Extensibilité**
- **Ajout facile** de nouveaux animaux dans `core`
- **Nouveaux composants QML** dans `components`
- **Extensions réseau** dans `network`

### 📦 **Organisation Build**
- **Fichiers temporaires** isolés dans `build`
- **Configuration centralisée** dans les fichiers `.pro` et `CMakeLists.txt`
- **Ressources organisées** avec préfixes logiques

## Convention de Nommage

### Fichiers C++
- **PascalCase** pour les classes : `LionManager.h`, `AlimentManager.cpp`
- **Extensions standard** : `.h` pour headers, `.cpp` pour sources

### Fichiers QML
- **PascalCase** pour les composants : `AnimatedLion.qml`, `DraggableAliment.qml`
- **Pages** dans le dossier `pages/`
- **Composants** dans le dossier `components/`

### Ressources
- **snake_case** pour les images : `lion_normal.png`, `lion_affame.png`
- **Préfixes logiques** dans qml.qrc : `/qml/` et `/images/`

## Migration depuis l'Ancienne Structure

Les changements principaux effectués :

1. **Déplacement des fichiers sources** vers `src/` avec sous-dossiers thématiques
2. **Réorganisation QML** avec séparation pages/composants
3. **Centralisation des ressources** dans `resources/`
4. **Mise à jour des includes** dans tous les fichiers
5. **Nouveau système de préfixes** dans qml.qrc
6. **Configuration build mise à jour** pour les nouveaux chemins

Cette structure facilite la collaboration, la maintenance et l'évolution future du projet.
