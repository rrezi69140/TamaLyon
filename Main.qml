import QtQuick
import QtQuick.Controls

Window {
    width: 500
    height: 700
    visible: true
    title: "Lion Tamagotchi"

    // Conteneur principal
    Item {
        anchors.fill: parent

        // MoodBar en haut à droite
        MoodBar {
            mood: lionManager.mood
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: 20
            anchors.rightMargin: 20
            z: 100
        }


        // Le lion centré
        LyonFace {
            id: face
            anchors.centerIn: parent
            width: 600
            height: 750
            z:0
        }
    }
}
