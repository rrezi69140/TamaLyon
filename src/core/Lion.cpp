#include "Lion.h"
#include <QDebug>

Lion::Lion(const QString &nom, QObject *parent)
    : Animal(nom, "Lion", parent)
{
    qDebug() << "[Lion] 🦁 Lion créé:" << nom;
}

void Lion::reagir(Aliment *aliment)
{
    if (!aliment) return;
    
    qDebug() << "[Lion] 🦁" << getNom() << "réagit à" << aliment->getNom();
    
    // Réactions spéciales selon la catégorie
    QString categorie = aliment->getCategorie();
    
    if (estCarnivorePrefere(categorie)) {
        // Le lion ADORE la viande
        qDebug() << "[Lion] 😍 ADORE la viande!";
        setHumeur(getHumeur() + 15); // Bonus humeur pour la viande
    }
    else if (categorie == "boisson" && aliment->getNom().contains("alcool", Qt::CaseInsensitive)) {
        // L'alcool rend le lion malade
        qDebug() << "[Lion] 🤢 L'alcool rend malade!";
        setEmpoisonnement(getEmpoisonnement() + 20);
        setHumeur(getHumeur() - 10);
    }
    else if (categorie == "legume") {
        // Le lion n'aime pas trop les légumes
        qDebug() << "[Lion] 😒 N'aime pas les légumes";
        setHumeur(getHumeur() - 5);
    }
    else if (categorie == "sucre") {
        // Le sucre donne de l'énergie mais peut être mauvais
        qDebug() << "[Lion] 🍭 Sucré mais pas idéal";
        setHumeur(getHumeur() + 5);
        if (aliment->getFaimImpact() > 15) {
            setEmpoisonnement(getEmpoisonnement() + 5); // Trop de sucre
        }
    }
    
    // Réaction selon l'état actuel
    switch (getEtat()) {
        case EtatAnimal::Affame:
            if (aliment->getFaimImpact() > 10) {
                setHumeur(getHumeur() + 10); // Bonus si très affamé
            }
            break;
            
        case EtatAnimal::Assoiffe:
            if (aliment->getSoifImpact() > 10) {
                setHumeur(getHumeur() + 10); // Bonus si très assoiffé
            }
            break;
            
        case EtatAnimal::Empoisonne:
            if (aliment->getEstToxique()) {
                qDebug() << "[Lion] 💀 Déjà empoisonné et mange du toxique!";
                setEmpoisonnement(getEmpoisonnement() + 15); // Double pénalité
            }
            break;
            
        default:
            break;
    }
}

QString Lion::getReactionMessage(Aliment *aliment) const
{
    if (!aliment) return "🦁 Aucune réaction";
    
    QString reaction = "🦁 " + getNom() + " ";
    
    // Message selon la catégorie
    reaction += getReactionParCategorie(aliment->getCategorie());
    
    // Ajouter des détails selon l'état
    reaction += " " + getReactionParEtat();
    
    // Ajouter emoji selon l'effet
    if (aliment->getEstToxique()) {
        reaction += " 🤢";
    } else if (estCarnivorePrefere(aliment->getCategorie())) {
        reaction += " 😍";
    } else if (aliment->getHumeurImpact() > 0) {
        reaction += " 😊";
    }
    
    return reaction;
}

bool Lion::accepteAliment(Aliment *aliment) const
{
    if (!aliment) return false;
    
    // Le lion refuse certains aliments selon les situations
    QString categorie = aliment->getCategorie();
    
    // Refuse les aliments végétariens stricts s'il est très affamé
    if (getEtat() == EtatAnimal::Affame && 
        (categorie == "legume" || categorie == "fruit") && 
        aliment->getFaimImpact() < 5) {
        qDebug() << "[Lion] Refuse" << aliment->getNom() << "- trop affamé pour des légumes";
        return false;
    }
    
    // Refuse l'alcool s'il est déjà empoisonné
    if (getEtat() == EtatAnimal::Empoisonne && 
        aliment->getNom().contains("alcool", Qt::CaseInsensitive)) {
        qDebug() << "[Lion] Refuse l'alcool - déjà empoisonné";
        return false;
    }
    
    // Refuse les aliments très toxiques s'il est en bonne santé (instinct)
    if (getEtat() == EtatAnimal::Normal && 
        aliment->getEstToxique() && 
        aliment->getEmpoisonnementLevel() > 30) { // Seuil plus élevé
        qDebug() << "[Lion] Instinct - refuse l'aliment très toxique";
        return false;
    }
    
    // Parfois le lion peut être curieux et accepter des aliments toxiques légers
    if (aliment->getEstToxique() && 
        aliment->getEmpoisonnementLevel() <= 30 && 
        getEtat() == EtatAnimal::Normal) {
        qDebug() << "[Lion] Curieux - accepte l'aliment toxique léger";
        // Le lion l'accepte mais sera plus méfiant
    }
    
    return true; // Accepte dans les autres cas
}

void Lion::onEtatChanged(EtatAnimal nouvelEtat)
{
    QString message;
    
    switch (nouvelEtat) {
        case EtatAnimal::Normal:
            message = "🦁 " + getNom() + " se sent bien!";
            break;
        case EtatAnimal::Affame:
            message = "😿 " + getNom() + " a très faim!";
            break;
        case EtatAnimal::Assoiffe:
            message = "💧 " + getNom() + " a très soif!";
            break;
        case EtatAnimal::Triste:
            message = "😢 " + getNom() + " est triste...";
            break;
        case EtatAnimal::Empoisonne:
            message = "🤢 " + getNom() + " est empoisonné!";
            break;
        case EtatAnimal::Mort:
            message = "💀 " + getNom() + " est mort...";
            break;
    }
    
    qDebug() << "[Lion]" << message;
    emit reactionAliment(message);
}

void Lion::onMort()
{
    qDebug() << "[Lion] 💀 Le roi de la savane est tombé...";
    emit reactionAliment("💀 " + getNom() + " le roi de la savane est mort! Appuyez sur Reset pour le ressusciter.");
}

QString Lion::getReactionParCategorie(const QString &categorie) const
{
    if (estCarnivorePrefere(categorie)) {
        return "dévore la viande avec appétit!";
    } else if (categorie == "boisson") {
        return "boit prudemment...";
    } else if (categorie == "legume") {
        return "grignote les légumes sans enthousiasme...";
    } else if (categorie == "fruit") {
        return "goûte le fruit par curiosité...";
    } else if (categorie == "sucre") {
        return "lèche le sucré avec plaisir...";
    } else {
        return "renifle et mange doucement...";
    }
}

QString Lion::getReactionParEtat() const
{
    switch (getEtat()) {
        case EtatAnimal::Affame:
            return "(il était affamé!)";
        case EtatAnimal::Assoiffe:
            return "(il avait soif!)";
        case EtatAnimal::Triste:
            return "(ça lui remonte le moral)";
        case EtatAnimal::Empoisonne:
            return "(il ne se sent pas bien...)";
        case EtatAnimal::Mort:
            return "(mais c'est trop tard...)";
        default:
            return "";
    }
}

bool Lion::estCarnivorePrefere(const QString &categorie) const
{
    return categorie == "viande" || 
           categorie == "poisson" || 
           categorie == "carnivore";
}
