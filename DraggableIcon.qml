import QtQuick

Item {
    id: root
    property string emoji
    property string type
    property bool available: true

    width: 50
    height: 50
    opacity: available ? 1.0 : 0.3
    
    // Propriété pour suivre si on est en train de draguer
    property bool isDragging: false
    
    // Propriété pour indiquer le type d'action
    property string dragType: type
    
    // Fonction pour marquer comme utilisé
    function markAsUsed() {
        console.log("[ICON] Marquer", type, "comme utilisé")
        available = false
        respawnTimer.start()
    }

    // Animation de pulsation quand disponible
    SequentialAnimation on scale {
        running: available
        loops: Animation.Infinite
        NumberAnimation { to: 1.1; duration: 1000; easing.type: Easing.InOutQuad }
        NumberAnimation { to: 1.0; duration: 1000; easing.type: Easing.InOutQuad }
    }

    Rectangle {
        anchors.fill: parent
        color: available ? "lightgreen" : "lightgray"
        radius: 25
        border.color: available ? "green" : "gray"
        border.width: 2
        opacity: available ? 0.7 : 0.3
    }
    
    // Overlay sombre quand indisponible
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: available ? 0.0 : 0.5
        radius: 25
        visible: !available
    }

    Text {
        text: emoji
        font.pixelSize: 30
        anchors.centerIn: parent
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        drag.target: available ? dragProxy : null
        enabled: available

        onPressed: {
            if (available) {
                console.log("[DRAG] Début du drag:", root.type, "- disponible:", available)
                dragProxy.x = 0
                dragProxy.y = 0
                root.isDragging = true
            }
        }

        onReleased: {
            console.log("[DRAG] Fin du drag:", root.type, "- était en train de draguer:", root.isDragging)
            
            if (root.isDragging) {
                // Vérifier si l'icône est au-dessus de la zone de drop
                let globalPos = dragProxy.mapToItem(null, dragProxy.width/2, dragProxy.height/2)
                console.log("[DRAG] Position globale au relâchement:", globalPos.x, globalPos.y)
                
                // Simuler un drop réussi si on détecte qu'on est dans la zone
                if (dragProxy.Drag.target) {
                    console.log("[DRAG] ✅ Drop détecté manuellement!")
                    
                    // Si on est en mode client, envoyer la commande au serveur
                    if (!lionManager.isHostMode()) {
                        console.log("[CLIENT] Envoi de la commande au serveur:", root.type)
                        lionManager.sendCommand(root.type)
                    } else {
                        // Si on est hôte, exécuter directement
                        console.log("[HOST] Exécution directe de l'action:", root.type)
                        if (root.type === "feed") {
                            console.log("[DROP] Nourrir le lion")
                            lionManager.feed(10)
                        } else if (root.type === "water") {
                            console.log("[DROP] Donner à boire au lion")
                            lionManager.water(10)
                        } else if (root.type === "pet") {
                            console.log("[DROP] Caresser le lion")
                            lionManager.pet(10)
                        }
                    }
                    
                    // Marquer comme utilisé
                    root.markAsUsed()
                } else {
                    console.log("[DRAG] ❌ Drop échoué")
                }
            }
            
            root.isDragging = false
            
            // Remettre le proxy à sa position d'origine
            dragProxy.x = 0
            dragProxy.y = 0
        }
    }

    // Proxy invisible pour le drag qui ne perturbe pas le layout
    Rectangle {
        id: dragProxy
        width: root.width
        height: root.height
        color: "transparent"
        border.color: "blue"
        border.width: 2
        visible: root.isDragging
        z: 1000
        
        Drag.active: mouseArea.drag.active
        Drag.hotSpot.x: 25
        Drag.hotSpot.y: 25
        Drag.mimeData: {
            "text/plain": root.type
        }
        
        Text {
            text: root.emoji
            font.pixelSize: 30
            anchors.centerIn: parent
        }
    }

    Timer {
        id: resetZTimer
        interval: 200
        onTriggered: {
            root.z = 0
        }
    }

    Timer {
        id: respawnTimer
        interval: 3000
        onTriggered: {
            root.available = true
            console.log("🔄 Icône", root.type, "rechargée et disponible")
        }
    }

    Behavior on opacity {
        NumberAnimation { duration: 500 }
    }

    Behavior on scale {
        NumberAnimation { duration: 200 }
    }
}
