
// MoodBar.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    property string mood: "joyeux"
    width: 300
    height: 80

    Rectangle {
        id: moodBackground
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        radius: height / 2
        z: 1

        gradient: Gradient {
            GradientStop { position: 0.0; color: mood === "joyeux" ? "#FFD700" :
                                            mood === "triste" ? "#2c3e50" :
                                            mood === "endormi" ? "#5B8DB8" :
                                            mood === "affame" ? "#7B3F00" :
                                            "#aaa" }
            GradientStop { position: 1.0; color: mood === "joyeux" ? "#FFA500" :
                                            mood === "triste" ? "#34495e" :
                                            mood === "endormi" ? "#7DA3C9" :
                                            mood === "affame" ? "#A0522D" :
                                            "#ccc" }
        }

        // Texte central
        Text {
            id: moodText
            text: mood.charAt(0).toUpperCase() + mood.slice(1)
            anchors.centerIn: parent
            font.pixelSize: mood === "affame" ? 28 : 22
            font.bold: true
            color: "white"
            opacity: 1

            Behavior on opacity {
                NumberAnimation { duration: 1000; easing.type: Easing.InOutQuad }
            }

            // Effet clignotant si endormi
            SequentialAnimation on opacity {
                running: mood === "endormi"
                loops: Animation.Infinite
                NumberAnimation { to: 0.3; duration: 600 }
                NumberAnimation { to: 1.0; duration: 600 }
            }

            // Grossissement si affamé
            Behavior on font.pixelSize {
                enabled: mood === "affame"
                NumberAnimation { duration: 500; easing.type: Easing.InOutQuad }
            }
        }
    }

    // ☀️ Rayons de soleil
    Repeater {
        model: mood === "joyeux" ? 12 : 0
        Rectangle {
            width: 6; height: 30
            color: "#FFA500"
            radius: 3
            x: root.width / 2 + Math.cos(index * 30 * Math.PI / 180) * 80 - width / 2
            y: root.height / 2 + Math.sin(index * 30 * Math.PI / 180) * 80 - height / 2
            RotationAnimator on rotation {
                from: 0
                to: 360
                duration: 4000
                loops: Animation.Infinite
            }
        }
    }

    // 💧 Gouttes de pluie si triste
    Repeater {
        model: mood === "triste" ? 10 : 0
        Rectangle {
            width: 4
            height: 12
            color: Qt.rgba(0.5, 0.7, 1, 0.7)
            x: Math.random() * root.width
            y: 0
            radius: 2
            z: 0

            PropertyAnimation {
                target: parent
                property: "y"
                from: 0
                to: root.height + 30
                duration: 1000 + Math.random() * 500
                loops: Animation.Infinite
                running: true
            }
        }
    }

    // 😴 ZZZ animés si endormi
    Repeater {
        model: mood === "endormi" ? 3 : 0
        Text {
            text: "Z"
            color: "blue"
            font.pixelSize: 20 + index * 4
            x: root.width - 40 + index * 8
            y: 10 + index * 10
            SequentialAnimation on y {
                loops: Animation.Infinite
                NumberAnimation { to: y - 20; duration: 1000 }
                PauseAnimation { duration: 300 }
                NumberAnimation { to: y; duration: 1000 }
            }
        }
    }

    // 🍗 Cuisses de poulet si affamé
    Repeater {
        model: mood === "affame" ? 3 : 0
        Text {
            text: "🍗"
            font.pixelSize: 22
            x: 10 + index * 20
            y: root.height
            SequentialAnimation on y {
                loops: Animation.Infinite
                NumberAnimation { to: y - 40; duration: 1500 + index * 100 }
                PauseAnimation { duration: 200 }
                NumberAnimation { to: y; duration: 1500 + index * 100 }
            }
        }
    }
}
