# 🔄 Test de Synchronisation Réseau - TamaLyon

## Architecture Serveur Autoritaire

La nouvelle architecture suit un modèle **serveur autoritaire** strict :

### 🎯 Fonctionnement

1. **Instance Hôte (Serveur)** :
   - ⚡ **Maître absolu** : Seul lui calcule la décroissance, l'état, les effets
   - 🔄 **Calcule tout** : Décroissance automatique, effets des aliments, changements d'état
   - 📡 **Diffuse** : Envoie l'état complet aux clients après chaque changement
   - 🎮 **Traite les commandes** : Reçoit les actions des clients et les applique

2. **Instance Cliente** :
   - 📱 **Interface passive** : Ne fait que afficher et envoyer des commandes
   - 🚫 **Ne calcule rien** : Pas de décroissance, pas d'application locale d'effets
   - 📤 **Envoie des commandes** : Transforme les actions utilisateur en commandes réseau
   - 📥 **Reçoit et applique** : Synchronise son affichage avec l'état du serveur

### 🧪 Test à Effectuer

1. **Démarrer les instances** :
   ```bash
   # Terminal 1 (Hôte - MAÎTRE)
   ./TamaLyon.app/Contents/MacOS/TamaLyon
   
   # Terminal 2 (Client - ESCLAVE)
   ./TamaLyon.app/Contents/MacOS/TamaLyon
   ```

2. **Connecter les instances** :
   - Instance 1 : Cliquer "🏠 Héberger" (devient le MAÎTRE)
   - Instance 2 : Cliquer "🔗 Rejoindre" (devient l'ESCLAVE)

3. **Tester la synchronisation autoritaire** :
   - Sur l'**hôte** : Glisser un aliment → Application immédiate + diffusion
   - Sur le **client** : Glisser un aliment → Commande au serveur → Le serveur applique → Le client reçoit le résultat
   - **Vérifier** : Seul l'hôte modifie réellement l'état

### 📊 Logs Attendus

**Côté Hôte (quand LUI ajoute un aliment)** :
```
[AlimentManager] � HÔTE - Application et diffusion
[AlimentManager] 📊 État AVANT - Faim: 80 [...]
[AlimentManager] 📊 État APRÈS - Faim: 105 [...]
[LionManager] 📢 Diffusion de l'état après changement
```

**Côté Client (quand LUI essaie d'ajouter un aliment)** :
```
[AlimentManager] 📡 CLIENT - Envoi commande au serveur (pas d'application locale)
[WebSocketClient] Commande envoyée: aliment:3
[LionManager] 📱 CLIENT - État reçu du serveur: {...}
[LionManager] 🔄 CLIENT - État local synchronisé avec le serveur
```

**Côté Hôte (quand il reçoit une commande du client)** :
```
[LionManager] 🏠 HÔTE - Commande reçue du client: aliment:3
[LionManager] 🍽️ HÔTE - Traitement commande aliment du CLIENT - Index: 3
[AlimentManager] � HÔTE - Application et diffusion
```

### ✅ Avantages de cette Architecture

- ✅ **Cohérence absolue** : Un seul maître, impossible d'avoir des conflits
- ✅ **Sécurité** : Le client ne peut pas tricher ou désynchroniser
- ✅ **Performance** : Le client est léger (pas de calculs)
- ✅ **Scalabilité** : Facilite l'ajout de plusieurs clients
- ✅ **Déterminisme** : Tous les clients voient exactement la même chose

### 🔍 Points de Vérification

1. **Décroissance** : Seul l'hôte voit ses barres diminuer automatiquement
2. **Client passif** : Le client ne change rien localement, tout vient du serveur
3. **Latence** : Les actions du client arrivent avec un léger délai (réseau)
4. **Synchronisation** : Les deux instances finissent toujours avec les mêmes valeurs

### 🐛 En Cas de Problème

Si ça ne fonctionne pas comme attendu :

1. **Vérifier les rôles** : L'hôte doit être démarré en premier avec "Héberger"
2. **Logs différents** : L'hôte et le client doivent avoir des logs très différents
3. **Client statique** : Si le client ne reçoit pas d'updates, vérifier la connexion WebSocket
4. **Hôte isolé** : Si l'hôte ne reçoit pas les commandes, vérifier le serveur WebSocket
