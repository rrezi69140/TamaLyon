import QtQuick

Item {
    id: root
    width: 600
    height: 750

    Image {
        id: lionImage
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit

        source: {
            if (lionManager.mood === "joyeux") return "qrc:/Images/FILES/lion_tres_content.png";
            if (lionManager.mood === "triste") return "qrc:/Images/FILES/lion_triste.png";
            if (lionManager.mood === "endormi") return "qrc:/Images/FILES/lion_endormi.png";
            if (lionManager.mood === "affame") return "qrc:/Images/FILES/lion_affame.png";
            return "qrc:/Images/FILES/lion_tres_content.png";
        }

        // Animation de respiration quand il dort
        SequentialAnimation on scale {
            running: lionManager.mood === "endormi"
            loops: Animation.Infinite
            NumberAnimation { to: 1.05; duration: 2000; easing.type: Easing.InOutQuad }
            NumberAnimation { to: 1.0; duration: 2000; easing.type: Easing.InOutQuad }
        }
    }

    // Effet Z quand le lion dort
    Text {
        text: "💤"
        font.pixelSize: 40
        anchors.right: lionImage.right
        anchors.top: lionImage.top
        anchors.margins: 20
        visible: lionManager.mood === "endormi"
        z: 5
        
        SequentialAnimation on opacity {
            running: lionManager.mood === "endormi"
            loops: Animation.Infinite
            NumberAnimation { to: 0.3; duration: 1500 }
            NumberAnimation { to: 1.0; duration: 1500 }
        }
    }



    DropArea {
        anchors.fill: lionImage
        z: 500  // S'assurer que la DropArea est au-dessus
        // Supprimer les clés pour accepter n'importe quel drop
        
        onDropped: (drop) => {
            console.log("[DROP] ✅ Drop détecté avec succès!")
            console.log("[DROP] Source:", drop.source ? drop.source.type : "AUCUNE")
            
            // Récupérer l'action depuis la source
            let action = ""
            if (drop.source && drop.source.type) {
                action = drop.source.type
            }
            console.log("[DROP] Action:", action)
            
            if (action === "feed") {
                console.log("[DROP] Nourrir le lion")
                lionManager.feed(10)
            } else if (action === "water") {
                console.log("[DROP] Donner à boire au lion")
                lionManager.water(10)
            } else if (action === "pet") {
                console.log("[DROP] Caresser le lion")
                lionManager.pet(10)
            }
            
            // Marquer l'icône source comme indisponible
            if (drop.source && drop.source.markAsUsed) {
                console.log("[DROP] Marquer icône comme utilisée")
                drop.source.markAsUsed()
            }
        }

        onEntered: (drag) => {
            console.log("[DROP] 🟢 Entrée dans la zone")
            console.log("[DROP] Source drag:", drag.source ? drag.source.type : "AUCUNE")
            lionImage.scale = 1.1
        }

        onExited: {
            console.log("[DROP] 🔴 Sortie de la zone")
            lionImage.scale = 1.0
        }
    }
}
