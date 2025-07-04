
import QtQuick 2.15

Item {
    id: root
    property string mood: "joyeux"
    width: 200
    height: 50

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

    // Barre d'humeur compacte
    Rectangle {
        id: moodBackground
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        radius: height / 2
        z: 1

        gradient: Gradient {
            GradientStop { position: 0.0; color: mood === "joyeux" ? "#FFD700" :
                                            mood === "triste" ? "#4682B4" :
                                            mood === "endormi" ? "#6A5ACD" :
                                            mood === "affame" ? "#DC143C" :
                                            "#aaa" }
            GradientStop { position: 1.0; color: mood === "joyeux" ? "#FFA500" :
                                            mood === "triste" ? "#87CEEB" :
                                            mood === "endormi" ? "#9370DB" :
                                            mood === "affame" ? "#FF6347" :
                                            "#ccc" }
        }

        // Texte de l'humeur
        Text {
            text: mood.charAt(0).toUpperCase() + mood.slice(1)
            anchors.centerIn: parent
            font.pixelSize: 14
            font.bold: true
            color: "white"
            style: Text.Outline
            styleColor: "black"
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
