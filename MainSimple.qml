import QtQuick
import QtQuick.Controls.Basic

Window {
    width: 400
    height: 600
    visible: true
    title: "Lion Tamagotchi - Simple"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "🦁 TamaLyon"
            font.pixelSize: 24
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Rectangle {
            width: 100
            height: 100
            color: "lightblue"
            border.color: "black"
            border.width: 2
            anchors.horizontalCenter: parent.horizontalCenter
            
            Text {
                anchors.centerIn: parent
                text: "Lion"
                font.bold: true
            }
        }

        Text {
            text: "Statut: " + lionManager.connectionStatus
            font.pixelSize: 14
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "Humeur: " + lionManager.mood
            font.pixelSize: 16
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Row {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                width: 100
                height: 40
                color: "lightgreen"
                border.color: "darkgreen"
                border.width: 2
                radius: 5

                Text {
                    anchors.centerIn: parent
                    text: "🏠 Héberger"
                    font.pixelSize: 12
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: lionManager.startAsHost()
                }
            }

            Rectangle {
                width: 100
                height: 40
                color: "lightblue"
                border.color: "darkblue"
                border.width: 2
                radius: 5

                Text {
                    anchors.centerIn: parent
                    text: "🔗 Rejoindre"
                    font.pixelSize: 12
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: lionManager.joinAsClient()
                }
            }
        }

        Row {
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                width: 80
                height: 30
                color: "orange"
                border.color: "red"
                border.width: 1
                radius: 4

                Text {
                    anchors.centerIn: parent
                    text: "🍖 Nourrir"
                    font.pixelSize: 10
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: lionManager.sendCommand("feed")
                }
            }

            Rectangle {
                width: 80
                height: 30
                color: "lightblue"
                border.color: "blue"
                border.width: 1
                radius: 4

                Text {
                    anchors.centerIn: parent
                    text: "💧 Abreuver"
                    font.pixelSize: 10
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: lionManager.sendCommand("drink")
                }
            }

            Rectangle {
                width: 80
                height: 30
                color: "pink"
                border.color: "purple"
                border.width: 1
                radius: 4

                Text {
                    anchors.centerIn: parent
                    text: "🎾 Jouer"
                    font.pixelSize: 10
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: lionManager.sendCommand("play")
                }
            }
        }
    }
}
