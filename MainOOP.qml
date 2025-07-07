import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

/**
 * @brief Interface principale avec la nouvelle architecture OOP
 */
Window {
    id: mainWindow
    width: 1000
    height: 800
    visible: true
    title: "🦁 TamaLyon - Architecture Orientée Objet"

    property bool isConnected: false

    // Image de fond globale
    Image {
        anchors.fill: parent
        source: "qrc:/FILES/background.png"
        fillMode: Image.PreserveAspectCrop
        opacity: 0.3
        z: -1
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        // En-tête avec titre et statut
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 80
            color: "#2C3E50"
            radius: 10
            border.color: "#34495E"
            border.width: 2

            RowLayout {
                anchors.fill: parent
                anchors.margins: 15
                spacing: 20

                // Titre principal
                Column {
                    Layout.alignment: Qt.AlignLeft
                    spacing: 5

                    Text {
                        text: "🦁 TamaLyon OOP"
                        font.pixelSize: 24
                        font.bold: true
                        color: "#ECF0F1"
                    }

                    Text {
                        text: "Architecture Orientée Objet avec Design Patterns"
                        font.pixelSize: 12
                        color: "#BDC3C7"
                        font.italic: true
                    }
                }

                // Informations du lion
                Column {
                    Layout.alignment: Qt.AlignCenter
                    spacing: 3

                    Text {
                        text: "🦁 " + lion.nom + " (" + lion.type + ")"
                        font.pixelSize: 16
                        font.bold: true
                        color: "#F39C12"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        text: "État: " + lion.etat
                        font.pixelSize: 12
                        color: lion.estMort ? "#E74C3C" : "#27AE60"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                // Boutons de contrôle
                Row {
                    Layout.alignment: Qt.AlignRight
                    spacing: 10

                    Button {
                        text: "🔄 Reset Lion"
                        onClicked: lion.resetAnimal()
                        enabled: lion.estMort
                    }

                    Button {
                        text: isConnected ? "📤 Host" : "🏠 Héberger"
                        onClicked: {
                            lionManager.startAsHost()
                            isConnected = true
                        }
                    }

                    Button {
                        text: isConnected ? "📥 Client" : "🔗 Rejoindre"
                        onClicked: {
                            lionManager.joinAsClient()
                            isConnected = true
                        }
                    }
                }
            }
        }

        // Interface principale
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 20

            // Panneau des aliments (gauche)
            Rectangle {
                Layout.preferredWidth: 300
                Layout.fillHeight: true
                color: "#34495E"
                radius: 10
                border.color: "#2C3E50"
                border.width: 2

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 15
                    spacing: 15

                    // Titre du panneau
                    Text {
                        text: "🍽️ Aliments Disponibles"
                        font.pixelSize: 18
                        font.bold: true
                        color: "#ECF0F1"
                        Layout.alignment: Qt.AlignHCenter
                    }

                    Text {
                        text: "Glissez les aliments sur le lion"
                        font.pixelSize: 12
                        color: "#BDC3C7"
                        Layout.alignment: Qt.AlignHCenter
                        wrapMode: Text.WordWrap
                        Layout.preferredWidth: parent.width - 30
                        horizontalAlignment: Text.AlignHCenter
                    }

                    // Grille d'aliments
                    ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        
                        GridLayout {
                            id: alimentGrid
                            columns: 3
                            columnSpacing: 10
                            rowSpacing: 10
                            anchors.left: parent.left
                            anchors.right: parent.right

                            // Générer les aliments dynamiquement
                            Repeater {
                                model: alimentManager.getAlimentCount()

                                DraggableAliment {
                                    aliment: alimentManager.getAlimentByIndex(index)
                                    alimentIndex: index
                                    Layout.preferredWidth: 80
                                    Layout.preferredHeight: 100

                                    onAlimentDropped: function(alimentData) {
                                        console.log("[Main] Aliment droppé:", alimentData.nom)
                                        lion.donnerAliment(alimentData)
                                    }
                                }
                            }
                        }
                    }

                    // Légende des effets
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 60
                        color: "#2C3E50"
                        radius: 8

                        Column {
                            anchors.centerIn: parent
                            spacing: 3

                            Text {
                                text: "Légende des effets:"
                                font.pixelSize: 10
                                font.bold: true
                                color: "#ECF0F1"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }

                            Row {
                                anchors.horizontalCenter: parent.horizontalCenter
                                spacing: 15

                                Row {
                                    spacing: 3
                                    Rectangle { width: 8; height: 8; radius: 4; color: "#4CAF50" }
                                    Text { text: "Faim+"; font.pixelSize: 8; color: "#BDC3C7" }
                                }

                                Row {
                                    spacing: 3
                                    Rectangle { width: 8; height: 8; radius: 4; color: "#2196F3" }
                                    Text { text: "Soif+"; font.pixelSize: 8; color: "#BDC3C7" }
                                }

                                Row {
                                    spacing: 3
                                    Rectangle { width: 8; height: 8; radius: 4; color: "#E91E63" }
                                    Text { text: "Toxique"; font.pixelSize: 8; color: "#BDC3C7" }
                                }
                            }
                        }
                    }
                }
            }

            // Zone centrale - Lion et stats
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 15

                // Zone du lion avec drop area
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "#ECF0F1"
                    radius: 15
                    border.color: "#BDC3C7"
                    border.width: 3

                    // DropArea pour recevoir les aliments
                    DropArea {
                        id: lionDropArea
                        anchors.fill: parent

                        onEntered: {
                            parent.color = "#D5DBDB"
                            parent.border.color = "#F39C12"
                            console.log("[DropArea] Aliment entré dans la zone")
                        }

                        onExited: {
                            parent.color = "#ECF0F1"
                            parent.border.color = "#BDC3C7"
                            console.log("[DropArea] Aliment sorti de la zone")
                        }

                        onDropped: function(drop) {
                            parent.color = "#ECF0F1"
                            parent.border.color = "#BDC3C7"
                            console.log("[DropArea] Drop détecté:", drop.text)
                            
                            // Nourrir le lion avec l'aliment droppé
                            if (alimentManager) {
                                var alimentIndex = parseInt(drop.text)
                                if (!isNaN(alimentIndex)) {
                                    console.log("[DropArea] 🎯 Nourrissage du lion avec l'aliment index:", alimentIndex)
                                    console.log("[DropArea] État du lion AVANT nourrissage - Faim:", lion.faim, "Soif:", lion.soif, "Humeur:", lion.humeur, "État:", lion.etat)
                                    alimentManager.nourrirLion(alimentIndex)
                                    console.log("[DropArea] État du lion APRÈS nourrissage - Faim:", lion.faim, "Soif:", lion.soif, "Humeur:", lion.humeur, "État:", lion.etat)
                                } else {
                                    console.log("[DropArea] ❌ Index d'aliment invalide:", drop.text)
                                }
                            } else {
                                console.log("[DropArea] ❌ alimentManager non disponible")
                            }
                        }
                    }

                    // Contenu de la zone du lion
                    ColumnLayout {
                        anchors.centerIn: parent
                        spacing: 20

                        // Lion animé
                        AnimatedLion {
                            id: animatedLion
                            lionRef: lion
                            Layout.preferredWidth: 200
                            Layout.preferredHeight: 200
                            Layout.alignment: Qt.AlignHCenter
                        }

                        // Nom et infos du lion
                        Column {
                            Layout.alignment: Qt.AlignHCenter
                            spacing: 5

                            Text {
                                text: lion.nom
                                font.pixelSize: 24
                                font.bold: true
                                color: "#2C3E50"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }

                            Text {
                                text: lion.etat + (lion.estMort ? " 💀" : "")
                                font.pixelSize: 14
                                color: lion.estMort ? "#E74C3C" : "#7F8C8D"
                                anchors.horizontalCenter: parent.horizontalCenter
                                font.italic: true
                            }
                        }
                    }
                }

                // Barres de statistiques
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 140
                    color: "#34495E"
                    radius: 10
                    border.color: "#2C3E50"
                    border.width: 2

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 15
                        spacing: 8

                        // Titre des statistiques
                        Text {
                            text: "📊 Statistiques du Lion"
                            font.pixelSize: 14
                            font.bold: true
                            color: "#ECF0F1"
                            Layout.alignment: Qt.AlignHCenter
                        }

                        // Faim
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 10

                            Text {
                                text: "🍖 Faim"
                                font.pixelSize: 12
                                color: "#ECF0F1"
                                Layout.minimumWidth: 70
                            }

                            Rectangle {
                                Layout.fillWidth: true
                                height: 15
                                color: "#2C3E50"
                                radius: 7

                                Rectangle {
                                    width: parent.width * (lion.faim / 100)
                                    height: parent.height
                                    color: lion.faim > 60 ? "#27AE60" : lion.faim > 30 ? "#F39C12" : "#E74C3C"
                                    radius: 7

                                    Behavior on width {
                                        NumberAnimation { duration: 500; easing.type: Easing.OutQuad }
                                    }
                                }
                            }

                            Text {
                                text: lion.faim + "%"
                                font.pixelSize: 10
                                color: "#BDC3C7"
                                Layout.minimumWidth: 35
                            }
                        }

                        // Soif
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 10

                            Text {
                                text: "💧 Soif"
                                font.pixelSize: 12
                                color: "#ECF0F1"
                                Layout.minimumWidth: 70
                            }

                            Rectangle {
                                Layout.fillWidth: true
                                height: 15
                                color: "#2C3E50"
                                radius: 7

                                Rectangle {
                                    width: parent.width * (lion.soif / 100)
                                    height: parent.height
                                    color: lion.soif > 60 ? "#3498DB" : lion.soif > 30 ? "#F39C12" : "#E74C3C"
                                    radius: 7

                                    Behavior on width {
                                        NumberAnimation { duration: 500; easing.type: Easing.OutQuad }
                                    }
                                }
                            }

                            Text {
                                text: lion.soif + "%"
                                font.pixelSize: 10
                                color: "#BDC3C7"
                                Layout.minimumWidth: 35
                            }
                        }

                        // Humeur
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 10

                            Text {
                                text: "😊 Humeur"
                                font.pixelSize: 12
                                color: "#ECF0F1"
                                Layout.minimumWidth: 70
                            }

                            Rectangle {
                                Layout.fillWidth: true
                                height: 15
                                color: "#2C3E50"
                                radius: 7

                                Rectangle {
                                    width: parent.width * (lion.humeur / 100)
                                    height: parent.height
                                    color: lion.humeur > 60 ? "#E91E63" : lion.humeur > 30 ? "#F39C12" : "#E74C3C"
                                    radius: 7

                                    Behavior on width {
                                        NumberAnimation { duration: 500; easing.type: Easing.OutQuad }
                                    }
                                }
                            }

                            Text {
                                text: lion.humeur + "%"
                                font.pixelSize: 10
                                color: "#BDC3C7"
                                Layout.minimumWidth: 35
                            }
                        }

                        // Empoisonnement
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 10

                            Text {
                                text: "🤢 Poison"
                                font.pixelSize: 12
                                color: "#ECF0F1"
                                Layout.minimumWidth: 70
                            }

                            Rectangle {
                                Layout.fillWidth: true
                                height: 15
                                color: "#2C3E50"
                                radius: 7

                                Rectangle {
                                    width: parent.width * (lion.empoisonnement / 100)
                                    height: parent.height
                                    color: lion.empoisonnement > 50 ? "#8E44AD" : lion.empoisonnement > 20 ? "#F39C12" : "#27AE60"
                                    radius: 7

                                    Behavior on width {
                                        NumberAnimation { duration: 500; easing.type: Easing.OutQuad }
                                    }
                                }
                            }

                            Text {
                                text: lion.empoisonnement + "%"
                                font.pixelSize: 10
                                color: "#BDC3C7"
                                Layout.minimumWidth: 35
                            }
                        }
                    }
                }
            }
        }

        // Panneau de messages/réactions du lion
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            color: "#2C3E50"
            radius: 10
            border.color: "#34495E"
            border.width: 2

            ScrollView {
                anchors.fill: parent
                anchors.margins: 10

                Text {
                    id: reactionText
                    text: "🦁 " + lion.nom + " attend de la nourriture..."
                    font.pixelSize: 14
                    color: "#ECF0F1"
                    wrapMode: Text.WordWrap
                    width: parent.width

                    // Connecter aux réactions du lion
                    Connections {
                        target: lion
                        function onReactionAliment(message) {
                            reactionText.text = message
                            reactionAnimation.restart()
                        }
                    }

                    // Animation pour les nouveaux messages
                    SequentialAnimation {
                        id: reactionAnimation
                        PropertyAnimation {
                            target: reactionText
                            property: "scale"
                            to: 1.1
                            duration: 200
                        }
                        PropertyAnimation {
                            target: reactionText
                            property: "scale"
                            to: 1.0
                            duration: 200
                        }
                    }
                }
            }
        }
    }
}
