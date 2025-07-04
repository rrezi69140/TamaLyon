import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 800
    height: 900
    visible: true
    title: "Lion Tamagotchi"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        // Titre et statut
        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 10

            Text {
                text: "🦁 TamaLyon"
                font.pixelSize: 32
                font.bold: true
                color: "#8B4513"
                Layout.alignment: Qt.AlignHCenter
            }

            Text {
                text: "Statut: " + lionManager.connectionStatus
                font.pixelSize: 16
                Layout.alignment: Qt.AlignHCenter
            }
        }

        // Boutons de connexion
        RowLayout {
            spacing: 20
            Layout.alignment: Qt.AlignHCenter

            Button {
                text: "🏠 Héberger"
                font.pixelSize: 16
                implicitWidth: 120
                implicitHeight: 40
                onClicked: lionManager.startAsHost()
            }

            Button {
                text: "🔗 Rejoindre"
                font.pixelSize: 16
                implicitWidth: 120
                implicitHeight: 40
                onClicked: lionManager.joinAsClient()
            }
        }

        // Interface principal du jeu
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 20

            // Panneau des objets draggables
            ColumnLayout {
                Layout.preferredWidth: 200
                Layout.fillHeight: true
                spacing: 20

                Text {
                    text: "Objets (rechargent toutes les 3s)"
                    font.pixelSize: 16
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }

                ColumnLayout {
                    spacing: 30

                    DraggableIcon {
                        emoji: "🍖"
                        type: "feed"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    DraggableIcon {
                        emoji: "💧"
                        type: "water"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    DraggableIcon {
                        emoji: "🎾"
                        type: "pet"
                        Layout.alignment: Qt.AlignHCenter
                    }
                }

                // Instructions
                Text {
                    text: "💡 Conseils:"
                    font.pixelSize: 14
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                    Layout.topMargin: 20
                }

                Text {
                    text: "• Caressez pour réveiller\n• Nourrissez régulièrement\n• Donnez de l'attention"
                    font.pixelSize: 12
                    Layout.alignment: Qt.AlignHCenter
                    wrapMode: Text.WordWrap
                    Layout.preferredWidth: 180
                }
            }

            // Zone du lion
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 10

                Text {
                    text: "Glissez les objets sur le lion"
                    font.pixelSize: 16
                    font.italic: true
                    Layout.alignment: Qt.AlignHCenter
                }

                LyonFace {
                    Layout.alignment: Qt.AlignHCenter
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }
        }
    }
}
