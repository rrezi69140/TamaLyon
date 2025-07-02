import QtQuick
import QtQuick.Controls


Window {
    width: 500
    height: 700
    visible: true
    title: "Lion Tamagotchi"

    Column {
        anchors.centerIn: parent
        spacing: 10

        LyonFace {
            width: 600
            height: 750
        }

    }
}
