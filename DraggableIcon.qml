import QtQuick

Item {
    id: root
    property string emoji
    property string type
    property bool available: true

    width: 50
    height: 50
    opacity: available ? 1.0 : 0.3

    Drag.active: mouseArea.drag.active
    Drag.hotSpot.x: 25
    Drag.hotSpot.y: 25
    // Supprimer les clés pour simplifier
    Drag.mimeData: {
        "text/plain": type
    }
    
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
        drag.target: available ? root : null
        enabled: available

        onPressed: {
            if (available) {
                console.log("[DRAG] Début du drag:", root.type, "- disponible:", available)
                root.z = 1000  // Mettre au premier plan
                root.isDragging = true
            }
        }

        onReleased: {
            console.log("[DRAG] Fin du drag:", root.type, "- était en train de draguer:", root.isDragging)
            
            if (root.isDragging) {
                // Vérifier si l'icône est au-dessus de la zone de drop
                let globalPos = root.mapToItem(null, root.width/2, root.height/2)
                console.log("[DRAG] Position globale au relâchement:", globalPos.x, globalPos.y)
                
                // Essayer de trouver le LyonFace et vérifier si on est dessus
                let parentWindow = root.parent
                while (parentWindow && !parentWindow.objectName) {
                    parentWindow = parentWindow.parent
                }
                
                // Simuler un drop réussi si on détecte qu'on est dans la zone
                if (root.Drag.target) {
                    console.log("[DRAG] ✅ Drop détecté manuellement!")
                    // Déclencher l'action directement
                    if (root.type === "feed") {
                        console.log("[DROP] Nourrir le lion")
                        lionManager.feed(2)
                    } else if (root.type === "water") {
                        console.log("[DROP] Donner à boire au lion")
                        lionManager.water(2)
                    } else if (root.type === "pet") {
                        console.log("[DROP] Caresser le lion")
                        lionManager.pet(3)
                    }
                    
                    // Marquer comme utilisé
                    root.markAsUsed()
                } else {
                    console.log("[DRAG] ❌ Drop échoué")
                }
            }
            
            root.isDragging = false
            
            // Retarder le retour à la position d'origine pour laisser le temps au drop de se faire
            returnToPositionTimer.start()
            
            // Retarder la remise à zéro du z-index pour permettre au drop de se terminer
            resetZTimer.start()
        }
    }

    Timer {
        id: returnToPositionTimer
        interval: 500  // Attendre 500ms avant de remettre l'icône à sa position
        onTriggered: {
            console.log("[DRAG] Retour à la position d'origine pour:", root.type)
            root.x = 0
            root.y = 0
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
