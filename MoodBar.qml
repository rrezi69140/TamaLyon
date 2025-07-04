
import QtQuick 2.15

Item {
    id: root
    property string mood: "joyeux"
    width: 350
    height: 80

    // Nettoyage des effets quand l'humeur change
    onMoodChanged: {
        // Arrêter tous les effets existants
        sunEffect.visible = false
        rainEffect.visible = false
        sleepEffect.visible = false
        fireEffect.visible = false
        
        // Démarrer le bon effet après un court délai
        effectTimer.start()
    }

    Timer {
        id: effectTimer
        interval: 100
        onTriggered: {
            sunEffect.visible = (mood === "joyeux")
            rainEffect.visible = (mood === "triste")
            sleepEffect.visible = (mood === "endormi")
            fireEffect.visible = (mood === "affame")
        }
    }

    // Barre d'humeur compacte avec stats
    Rectangle {
        id: moodBackground
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        radius: 10
        z: 1
        color: "#2C3E50"
        border.color: "#34495E"
        border.width: 2

        // Titre de l'humeur
        Text {
            text: mood.charAt(0).toUpperCase() + mood.slice(1)
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
            font.pixelSize: 12
            font.bold: true
            color: "white"
        }

        // Barres de stats
        Row {
            anchors.centerIn: parent
            spacing: 15
            
            // Barre de faim
            Column {
                spacing: 2
                Text {
                    text: "🍖"
                    font.pixelSize: 16
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Rectangle {
                    width: 60
                    height: 8
                    radius: 4
                    color: "#34495E"
                    Rectangle {
                        width: parent.width * (lionManager.hunger / 100)
                        height: parent.height
                        radius: 4
                        color: lionManager.hunger > 60 ? "#27AE60" : 
                               lionManager.hunger > 30 ? "#F39C12" : "#E74C3C"
                        
                        Behavior on width {
                            NumberAnimation { duration: 500; easing.type: Easing.OutQuad }
                        }
                    }
                }
                Text {
                    text: Math.round(lionManager.hunger) + "%"
                    font.pixelSize: 9
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            
            // Barre de soif
            Column {
                spacing: 2
                Text {
                    text: "💧"
                    font.pixelSize: 16
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Rectangle {
                    width: 60
                    height: 8
                    radius: 4
                    color: "#34495E"
                    Rectangle {
                        width: parent.width * (lionManager.thirst / 100)
                        height: parent.height
                        radius: 4
                        color: lionManager.thirst > 60 ? "#3498DB" : 
                               lionManager.thirst > 30 ? "#F39C12" : "#E74C3C"
                        
                        Behavior on width {
                            NumberAnimation { duration: 500; easing.type: Easing.OutQuad }
                        }
                    }
                }
                Text {
                    text: Math.round(lionManager.thirst) + "%"
                    font.pixelSize: 9
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            
            // Barre d'affection
            Column {
                spacing: 2
                Text {
                    text: "💖"
                    font.pixelSize: 16
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Rectangle {
                    width: 60
                    height: 8
                    radius: 4
                    color: "#34495E"
                    Rectangle {
                        width: parent.width * (lionManager.affection / 100)
                        height: parent.height
                        radius: 4
                        color: lionManager.affection > 60 ? "#E91E63" : 
                               lionManager.affection > 30 ? "#F39C12" : "#E74C3C"
                        
                        Behavior on width {
                            NumberAnimation { duration: 500; easing.type: Easing.OutQuad }
                        }
                    }
                }
                Text {
                    text: Math.round(lionManager.affection) + "%"
                    font.pixelSize: 9
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            
            // Barre d'énergie
            Column {
                spacing: 2
                Text {
                    text: "⚡"
                    font.pixelSize: 16
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Rectangle {
                    width: 60
                    height: 8
                    radius: 4
                    color: "#34495E"
                    Rectangle {
                        width: parent.width * (lionManager.energy / 100)
                        height: parent.height
                        radius: 4
                        color: lionManager.energy > 60 ? "#9B59B6" : 
                               lionManager.energy > 30 ? "#F39C12" : "#E74C3C"
                        
                        Behavior on width {
                            NumberAnimation { duration: 500; easing.type: Easing.OutQuad }
                        }
                    }
                }
                Text {
                    text: Math.round(lionManager.energy) + "%"
                    font.pixelSize: 9
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
        }
        
        // Conseil utile
        Text {
            text: {
                if (lionManager.hunger < 30) return "💡 Nourrir le lion"
                if (lionManager.thirst < 30) return "💡 Hydrater le lion"
                if (lionManager.affection < 30) return "💡 Caresser le lion"
                if (lionManager.energy < 30) return "💡 Laisser dormir"
                return "💡 Tout va bien!"
            }
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 3
            font.pixelSize: 10
            color: "white"
            font.bold: true
        }
    }

    // ✨ Effet SOLEIL pour joyeux
    Item {
        id: sunEffect
        anchors.fill: parent
        visible: mood === "joyeux"
        
        Repeater {
            model: 8
            Rectangle {
                width: 3
                height: 15
                color: "#FFD700"
                radius: 2
                x: parent.width/2 + Math.cos(index * 45 * Math.PI / 180) * 30 - width/2
                y: parent.height/2 + Math.sin(index * 45 * Math.PI / 180) * 30 - height/2
                
                RotationAnimation on rotation {
                    from: 0
                    to: 360
                    duration: 3000
                    loops: Animation.Infinite
                    running: parent.visible
                }
            }
        }
    }

    // 🌧️ Effet PLUIE pour triste
    Item {
        id: rainEffect
        anchors.fill: parent
        visible: mood === "triste"
        
        Repeater {
            model: 6
            Rectangle {
                width: 2
                height: 10
                color: "#4682B4"
                x: 20 + index * 25
                y: 0
                
                SequentialAnimation on y {
                    loops: Animation.Infinite
                    running: parent.visible
                    NumberAnimation { to: parent.height + 10; duration: 1000 + index * 100 }
                    NumberAnimation { to: 0; duration: 0 }
                }
            }
        }
    }

    // 💤 Effet BULLES pour endormi
    Item {
        id: sleepEffect
        anchors.fill: parent
        visible: mood === "endormi"
        
        Repeater {
            model: 4
            Rectangle {
                width: 8
                height: 8
                color: "transparent"
                border.color: "#6A5ACD"
                border.width: 1
                radius: 4
                x: 30 + index * 20
                y: parent.height - 10
                
                SequentialAnimation on y {
                    loops: Animation.Infinite
                    running: parent.visible
                    NumberAnimation { to: -10; duration: 2000 + index * 200 }
                    NumberAnimation { to: parent.height - 10; duration: 0 }
                }
            }
        }
    }

    // 🔥 Effet FEU pour affamé
    Item {
        id: fireEffect
        anchors.fill: parent
        visible: mood === "affame"
        
        Repeater {
            model: 6
            Rectangle {
                width: 4
                height: 8
                color: index % 2 === 0 ? "#FF4500" : "#FF6347"
                x: 25 + index * 20
                y: parent.height - 5
                
                SequentialAnimation on height {
                    loops: Animation.Infinite
                    running: parent.visible
                    NumberAnimation { to: 12; duration: 300 + index * 50 }
                    NumberAnimation { to: 6; duration: 300 + index * 50 }
                }
            }
        }
    }
}
