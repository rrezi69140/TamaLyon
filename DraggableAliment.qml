import QtQuick
import QtQuick.Controls

/**
 * @brief Composant QML pour les objets draggables
 * Encapsule un aliment et permet le drag & drop
 */
Item {
    id: root
    
    // Propriétés publiques
    property var aliment: null
    property int alimentIndex: -1
    property bool available: true
    property bool isDragging: false
    property alias mouseArea: mouseArea
    
    // Signaux
    signal alimentDropped(var aliment)
    signal dragStarted()
    signal dragEnded()
    
    width: 80
    height: 100
    opacity: available ? 1.0 : 0.3
    
    // État de l'élément
    states: [
        State {
            name: "normal"
            when: !isDragging && available
            PropertyChanges { target: root; scale: 1.0 }
            PropertyChanges { target: background; color: "#4CAF50" }
        },
        State {
            name: "dragging"
            when: isDragging
            PropertyChanges { target: root; scale: 1.1 }
            PropertyChanges { target: background; color: "#FF9800" }
        },
        State {
            name: "unavailable"
            when: !available
            PropertyChanges { target: root; scale: 0.9 }
            PropertyChanges { target: background; color: "#9E9E9E" }
        }
    ]
    
    // Transitions entre états
    transitions: [
        Transition {
            NumberAnimation { properties: "scale"; duration: 200; easing.type: Easing.OutQuad }
            ColorAnimation { duration: 300 }
        }
    ]
    
    // Fonction pour marquer comme utilisé
    function markAsUsed() {
        if (aliment) {
            console.log("[DraggableItem] Marquer", aliment.nom, "comme utilisé")
            available = false
            respawnTimer.restart()
        }
    }
    
    // Fonction pour vérifier la validité de l'aliment
    function isValid() {
        return aliment !== null && aliment !== undefined
    }
    
    // Background de l'élément
    Rectangle {
        id: background
        anchors.fill: parent
        radius: 15
        border.width: 2
        border.color: available ? "#388E3C" : "#616161"
        
        // Dégradé selon l'état
        gradient: Gradient {
            GradientStop { 
                position: 0.0
                color: Qt.lighter(background.color, 1.2)
            }
            GradientStop { 
                position: 1.0
                color: Qt.darker(background.color, 1.1)
            }
        }
    }
    
    // Overlay sombre quand indisponible
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: available ? 0.0 : 0.4
        radius: 15
        visible: !available
        
        // Animation de fondu
        Behavior on opacity {
            NumberAnimation { duration: 300 }
        }
    }
    
    // Contenu de l'aliment
    Column {
        anchors.centerIn: parent
        spacing: 5
        
        // Emoji de l'aliment
        Text {
            id: emojiText
            text: aliment ? aliment.emoji : "❓"
            font.pixelSize: 32
            anchors.horizontalCenter: parent.horizontalCenter
            
            // Animation de pulsation quand disponible
            SequentialAnimation on scale {
                running: available && !isDragging
                loops: Animation.Infinite
                NumberAnimation { to: 1.1; duration: 1500; easing.type: Easing.InOutQuad }
                NumberAnimation { to: 1.0; duration: 1500; easing.type: Easing.InOutQuad }
            }
        }
        
        // Nom de l'aliment
        Text {
            text: aliment ? aliment.nom : "Inconnu"
            font.pixelSize: 10
            font.bold: true
            color: available ? "white" : "#BDBDBD"
            anchors.horizontalCenter: parent.horizontalCenter
            wrapMode: Text.WordWrap
            width: root.width - 10
            horizontalAlignment: Text.AlignHCenter
        }
        
        // Indicateurs d'effets (optionnel)
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 2
            visible: aliment && available
            
            // Indicateur de faim
            Rectangle {
                width: 8
                height: 8
                radius: 4
                color: aliment && aliment.faimImpact > 0 ? "#4CAF50" : 
                       aliment && aliment.faimImpact < 0 ? "#F44336" : "transparent"
                visible: aliment && aliment.faimImpact !== 0
            }
            
            // Indicateur de soif
            Rectangle {
                width: 8
                height: 8
                radius: 4
                color: aliment && aliment.soifImpact > 0 ? "#2196F3" : 
                       aliment && aliment.soifImpact < 0 ? "#FF5722" : "transparent"
                visible: aliment && aliment.soifImpact !== 0
            }
            
            // Indicateur toxique
            Rectangle {
                width: 8
                height: 8
                radius: 4
                color: "#E91E63"
                visible: aliment && aliment.estToxique
            }
        }
    }
    
    // Zone de détection de la souris
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        enabled: available && isValid()
        
        drag.target: available ? dragProxy : null
        
        onPressed: {
            if (available && isValid()) {
                console.log("[DraggableItem] Début du drag:", aliment.nom)
                dragProxy.x = 0
                dragProxy.y = 0
                isDragging = true
                dragStarted()
            }
        }
        
        onReleased: {
            console.log("[DraggableItem] Fin du drag:", aliment ? aliment.nom : "null")
            
            if (isDragging && isValid()) {
                // Vérifier si on a droppé sur une cible valide
                let globalPos = dragProxy.mapToItem(null, dragProxy.width/2, dragProxy.height/2)
                console.log("[DraggableItem] Position globale au relâchement:", globalPos.x, globalPos.y)
                
                if (dragProxy.Drag.target) {
                    console.log("[DraggableItem] ✅ Drop détecté sur cible valide!")
                    alimentDropped(aliment)
                    markAsUsed()
                } else {
                    console.log("[DraggableItem] ❌ Drop échoué - pas de cible")
                }
            }
            
            isDragging = false
            dragEnded()
            
            // Remettre le proxy à sa position d'origine
            dragProxy.x = 0
            dragProxy.y = 0
        }
    }
    
    // Proxy invisible pour le drag
    Rectangle {
        id: dragProxy
        width: root.width
        height: root.height
        color: "transparent"
        border.color: "#FF9800"
        border.width: 3
        radius: 15
        visible: isDragging
        z: 1000
        
        Drag.active: mouseArea.drag.active
        Drag.hotSpot.x: width / 2
        Drag.hotSpot.y: height / 2
        Drag.mimeData: {
            "application/x-aliment": aliment ? aliment.nom : "",
            "text/plain": alimentIndex.toString()
        }
        
        // Contenu du proxy (copie de l'original)
        Column {
            anchors.centerIn: parent
            spacing: 5
            
            Text {
                text: aliment ? aliment.emoji : "❓"
                font.pixelSize: 32
                anchors.horizontalCenter: parent.horizontalCenter
            }
            
            Text {
                text: aliment ? aliment.nom : "Inconnu"
                font.pixelSize: 10
                font.bold: true
                color: "#FF9800"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        
        // Effet de brillance pendant le drag
        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: "#FFC107"
            border.width: 1
            radius: 15
            opacity: 0.6
            
            SequentialAnimation on opacity {
                running: dragProxy.visible
                loops: Animation.Infinite
                NumberAnimation { to: 1.0; duration: 500 }
                NumberAnimation { to: 0.3; duration: 500 }
            }
        }
    }
    
    // Timer de rechargement
    Timer {
        id: respawnTimer
        interval: 4000 // 4 secondes
        onTriggered: {
            available = true
            if (aliment) {
                console.log("🔄 Aliment", aliment.nom, "rechargé et disponible")
            }
        }
    }
    
    // Info bulle (optionnel)
    Rectangle {
        id: tooltip
        width: tooltipText.width + 20
        height: tooltipText.height + 10
        color: "#333333"
        radius: 5
        opacity: 0
        visible: opacity > 0
        z: 999
        
        anchors.bottom: root.top
        anchors.horizontalCenter: root.horizontalCenter
        anchors.bottomMargin: 5
        
        Text {
            id: tooltipText
            anchors.centerIn: parent
            text: aliment ? aliment.description : ""
            color: "white"
            font.pixelSize: 9
            wrapMode: Text.WordWrap
            width: Math.min(implicitWidth, 200)
        }
        
        // Afficher au survol (si pas en train de draguer)
        states: [
            State {
                name: "visible"
                when: mouseArea.containsMouse && !isDragging && available
                PropertyChanges { target: tooltip; opacity: 0.9 }
            }
        ]
        
        transitions: [
            Transition {
                NumberAnimation { property: "opacity"; duration: 200 }
            }
        ]
    }
    
    // Permettre le survol
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        enabled: false // Ne bloque pas les interactions
        z: -1
    }
}
