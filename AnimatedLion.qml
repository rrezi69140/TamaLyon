import QtQuick
import QtQuick.Controls

/**
 * @brief Composant lion animé avec support d'images PNG
 */
Item {
    id: lionComponent
    
    // Référence directe au lion (renommé pour éviter conflit)
    property QtObject lionRef: null
    
    // Propriétés d'animation
    property bool isEating: false
    property bool isBlinking: false
    property int currentFrame: 0
    
    width: 200
    height: 200
    
    // Debug: Log quand le lion change
    onLionRefChanged: {
        console.log("[AnimatedLion] 🦁 LION CHANGÉ!")
        if (lionRef) {
            console.log("[AnimatedLion] ✅ Lion connecté:", lionRef.nom)
            console.log("[AnimatedLion] 📊 État initial - Faim:", lionRef.faim, "Soif:", lionRef.soif, "Humeur:", lionRef.humeur, "État:", lionRef.etat)
        } else {
            console.log("[AnimatedLion] ❌ Lion null!")
        }
    }
    
    // Image principale du lion
    Item {
        id: lionContainer
        anchors.fill: parent
        
        // Image PNG (si disponible) - avec mise à jour automatique
        Image {
            id: lionImage
            anchors.fill: parent
            source: getCurrentImageSource  // CORRECTION: Utilise la propriété calculée
            fillMode: Image.PreserveAspectFit
            smooth: true
            visible: status === Image.Ready
            
            onStatusChanged: {
                if (status === Image.Error) {
                    console.log("[AnimatedLion] ❌ Image non trouvée:", source)
                } else if (status === Image.Ready) {
                    console.log("[AnimatedLion] ✅ Image chargée:", source)
                }
            }
            
            onSourceChanged: {
                console.log("[AnimatedLion] 🔄 Source d'image changée:", source)
            }
        }
        
        // Fallback avec émoji si image PNG non disponible
        Text {
            id: lionEmoji
            anchors.centerIn: parent
            text: lionRef ? getCurrentEmoji : "🦁"
            font.pixelSize: 120
            visible: lionImage.status !== Image.Ready
        }
        

        
        // Animation de respiration (toujours active)
        SequentialAnimation on scale {
            running: true // Toujours en cours pour être visible
            loops: Animation.Infinite
            NumberAnimation { to: 1.08; duration: 1500; easing.type: Easing.InOutQuad }
            NumberAnimation { to: 1.0; duration: 1500; easing.type: Easing.InOutQuad }
        }
        
        // Animation de rotation légère (toujours active)
        SequentialAnimation on rotation {
            running: true // Toujours en cours pour être visible
            loops: Animation.Infinite
            NumberAnimation { to: 2; duration: 3000; easing.type: Easing.InOutQuad }
            NumberAnimation { to: -2; duration: 3000; easing.type: Easing.InOutQuad }
            NumberAnimation { to: 0; duration: 2000; easing.type: Easing.InOutQuad }
        }
    }
    
    // Animations pour l'effet de manger
    PropertyAnimation {
        id: scaleUpAnimation
        target: lionContainer
        property: "scale"
        to: 1.2
        duration: 600
        easing.type: Easing.OutBounce
        onFinished: scaleDownAnimation.start()
    }
    
    PropertyAnimation {
        id: scaleDownAnimation
        target: lionContainer
        property: "scale"
        to: 1.0
        duration: 400
        easing.type: Easing.InOutQuad
    }
    
    // Animation de transition d'état
    SequentialAnimation {
        id: stateTransitionAnimation
        PropertyAnimation {
            target: lionContainer
            property: "scale"
            to: 0.8
            duration: 200
        }
        PropertyAnimation {
            target: lionContainer
            property: "scale"
            to: 1.0
            duration: 300
            easing.type: Easing.OutBounce
        }
    }
    
    // Animation de clignotement
    Timer {
        id: blinkTimer
        interval: 2000 + Math.random() * 1000 // 2-3 secondes pour plus de fréquence
        running: true // Toujours actif pour être visible
        repeat: true
        onTriggered: {
            blinkAnimation.start()
        }
    }
    
    // Animation de manger
    Timer {
        id: eatTimer
        interval: 200
        running: isEating
        repeat: true
        onTriggered: {
            currentFrame = (currentFrame + 1) % 3
            if (currentFrame === 0) {
                isEating = false
            }
        }
    }
    
    // Animation de clignotement
    SequentialAnimation {
        id: blinkAnimation
        PropertyAnimation {
            target: lionContainer
            property: "opacity"
            to: 0.3
            duration: 100
        }
        PropertyAnimation {
            target: lionContainer
            property: "opacity"
            to: 1.0
            duration: 100
        }
    }
    
    // Animation quand le lion mange
    function startEatingAnimation() {
        isEating = true
        currentFrame = 0
        eatTimer.start()
        
        // Démarrer l'animation de croissance
        scaleUpAnimation.start()
    }
    
    // Propriétés calculées qui se mettent à jour automatiquement
    property string getCurrentImageSource: {
        var imageSource = ""
        
        if (isEating) {
            imageSource = "qrc:/FILES/lion_mange_0" + (currentFrame + 1) + ".png"
            console.log("[AnimatedLion] 🍽️ Mode manger - Frame:", currentFrame + 1, "Image:", imageSource)
            return imageSource
        }
        
        if (!lionRef) {
            imageSource = "qrc:/FILES/lion_normal.png"
            console.log("[AnimatedLion] ⚠️ Pas de lion - Image par défaut:", imageSource)
            return imageSource
        }
        
        console.log("[AnimatedLion] 📊 État actuel du lion - Faim:", lionRef.faim, "Soif:", lionRef.soif, "Humeur:", lionRef.humeur, "État:", lionRef.etat, "EstMort:", lionRef.estMort)
        
        if (lionRef.estMort) {
            imageSource = "qrc:/FILES/lion_mort.png"
            console.log("[AnimatedLion] 💀 Lion mort - Image:", imageSource)
            return imageSource
        }
        
        switch (lionRef.etat) {
            case "Normal":
                imageSource = lionRef.humeur > 80 ? "qrc:/FILES/lion_tres_content.png" : "qrc:/FILES/lion_normal.png"
                console.log("[AnimatedLion] 😊 État Normal - Humeur:", lionRef.humeur, "Image:", imageSource)
                break
            case "Affamé":
                imageSource = "qrc:/FILES/lion_affame.png"
                console.log("[AnimatedLion] 🍽️ État Affamé - Image:", imageSource)
                break
            case "Assoiffé":
                imageSource = "qrc:/FILES/lion_assoiffe.png"
                console.log("[AnimatedLion] 🥤 État Assoiffé - Image:", imageSource)
                break
            case "Triste":
                imageSource = "qrc:/FILES/lion_triste.png"
                console.log("[AnimatedLion] 😢 État Triste - Image:", imageSource)
                break
            case "Empoisonné":
                imageSource = "qrc:/FILES/lion_empoisonne.png"
                console.log("[AnimatedLion] 🤢 État Empoisonné - Image:", imageSource)
                break
            case "Endormi":
                imageSource = "qrc:/FILES/lion_endormi.png"
                console.log("[AnimatedLion] 😴 État Endormi - Image:", imageSource)
                break
            default:
                imageSource = "qrc:/FILES/lion_normal.png"
                console.log("[AnimatedLion] ❓ État inconnu '" + lionRef.etat + "' - Image par défaut:", imageSource)
                break
        }
        
        return imageSource
    }
    
    property string getCurrentEmoji: {
        if (!lionRef) return "🦁"
        
        if (lionRef.estMort) {
            return "💀"
        }
        
        switch (lionRef.etat) {
            case "Normal":
                return lionRef.humeur > 80 ? "😸" : "🦁"
            case "Affamé":
                return "😿"
            case "Assoiffé":
                return "🥵"
            case "Triste":
                return "😢"
            case "Empoisonné":
                return "🤢"
            case "Endormi":
                return "😴"
            default:
                return "🦁"
        }
    }
    
    // Connexions pour les animations
    Connections {
        target: lionRef
        function onReactionAliment(message) {
            console.log("[AnimatedLion] 🍽️ Réaction à l'aliment:", message)
            lionComponent.startEatingAnimation()
        }
        
        function onEtatChanged() {
            console.log("[AnimatedLion] 🔄 CHANGEMENT D'ÉTAT DÉTECTÉ!")
            console.log("[AnimatedLion] 📊 Nouvel état:", lionRef.etat)
            console.log("[AnimatedLion] 📊 Faim:", lionRef.faim, "Soif:", lionRef.soif, "Humeur:", lionRef.humeur)
            console.log("[AnimatedLion] 🖼️ Nouvelle image:", getCurrentImageSource)
            // Animation de transition d'état
            stateTransitionAnimation.start()
        }
        
        function onHumeurChanged() {
            console.log("[AnimatedLion] 😊 Humeur changée:", lionRef.humeur)
            // Force la mise à jour de l'image
            lionImage.source = Qt.binding(function() { return getCurrentImageSource })
        }
        
        function onEstMortChanged() {
            console.log("[AnimatedLion] 💀 État de mort changé:", lionRef.estMort)
            if (lionRef.estMort) {
                console.log("[AnimatedLion] ⚰️ LE LION EST MORT!")
            }
            // Force la mise à jour de l'image
            lionImage.source = Qt.binding(function() { return getCurrentImageSource })
        }
        
        function onFaimChanged() {
            console.log("[AnimatedLion] 🍽️ Faim changée:", lionRef.faim)
            // Force la mise à jour de l'image
            lionImage.source = Qt.binding(function() { return getCurrentImageSource })
        }
        
        function onSoifChanged() {
            console.log("[AnimatedLion] 🥤 Soif changée:", lionRef.soif)
            // Force la mise à jour de l'image
            lionImage.source = Qt.binding(function() { return getCurrentImageSource })
        }
    }
}
