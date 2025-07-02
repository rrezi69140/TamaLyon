import QtQuick

Item {
    id: root
    width: 600
    height: 750


    Image {
        id: lionImage
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit

        source: {
            if (lionManager.mood === "joyeux") {
                return "qrc:/FILES/lion_tres_content.png"
            }
            if (lionManager.mood === "triste") {
                return "qrc:/FILES/lion_triste.png"
            }
            if (lionManager.mood === "endormi") {
                return "qrc:/FILES/lion_endormi.png"
            }
            if (lionManager.mood === "affame") {
                return "qrc:/FILES/lion_affame.png"
            }
            return ""
        }
    }
}
