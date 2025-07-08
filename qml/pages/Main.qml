import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 900
    height: 1000
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
                color: lionManager.connectionStatus.includes("actif") || lionManager.connectionStatus.includes("Connecté") ? "green" : "black"
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

        // Panneau de stats rapides en bas
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            color: "#34495E"
            radius: 10
            border.color: "#2C3E50"
            border.width: 2

            Row {
                anchors.centerIn: parent
                spacing: 40

                // Icône de faim avec valeur
                Column {
                    spacing: 3
                    anchors.verticalCenter: parent.verticalCenter
                    
                    Text {
                        text: "🍖"
                        font.pixelSize: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: (lionManager.hunger !== undefined && !isNaN(lionManager.hunger)) ? Math.round(lionManager.hunger) + "%" : "0%"
                        font.pixelSize: 11
                        color: lionManager.hunger > 60 ? "#27AE60" : 
                               lionManager.hunger > 30 ? "#F39C12" : "#E74C3C"
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                    }
                }

                // Icône de soif avec valeur
                Column {
                    spacing: 3
                    anchors.verticalCenter: parent.verticalCenter
                    
                    Text {
                        text: "💧"
                        font.pixelSize: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: (lionManager.thirst !== undefined && !isNaN(lionManager.thirst)) ? Math.round(lionManager.thirst) + "%" : "0%"
                        font.pixelSize: 11
                        color: lionManager.thirst > 60 ? "#3498DB" : 
                               lionManager.thirst > 30 ? "#F39C12" : "#E74C3C"
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                    }
                }

                // Icône d'affection avec valeur
                Column {
                    spacing: 3
                    anchors.verticalCenter: parent.verticalCenter
                    
                    Text {
                        text: "💖"
                        font.pixelSize: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: (lionManager.affection !== undefined && !isNaN(lionManager.affection)) ? Math.round(lionManager.affection) + "%" : "0%"
                        font.pixelSize: 11
                        color: lionManager.affection > 60 ? "#E91E63" : 
                               lionManager.affection > 30 ? "#F39C12" : "#E74C3C"
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                    }
                }

                // Icône d'énergie avec valeur
                Column {
                    spacing: 3
                    anchors.verticalCenter: parent.verticalCenter
                    
                    Text {
                        text: "⚡"
                        font.pixelSize: 20
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: (lionManager.energy !== undefined && !isNaN(lionManager.energy)) ? Math.round(lionManager.energy) + "%" : "0%"
                        font.pixelSize: 11
                        color: lionManager.energy > 60 ? "#9B59B6" : 
                               lionManager.energy > 30 ? "#F39C12" : "#E74C3C"
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                    }
                }

                // Conseil intégré selon l'état
                Column {
                    spacing: 3
                    anchors.verticalCenter: parent.verticalCenter
                    
                    Text {
                        text: "💡"
                        font.pixelSize: 18
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: {
                            if (lionManager.hunger < 30) return "Nourrir"
                            if (lionManager.thirst < 30) return "Hydrater"
                            if (lionManager.affection < 30) return "Caresser"
                            if (lionManager.energy < 30) return "Dormir"
                            return "Tout va bien!"
                        }
                        font.pixelSize: 10
                        color: "white"
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                    }
                }
            }
        }
    }
}
