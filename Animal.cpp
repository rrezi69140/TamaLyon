#include "Animal.h"
#include "EffectHandler.h"
#include <QDebug>

Animal::Animal(const QString &nom, const QString &type, QObject *parent)
    : QObject(parent),
      faim(100),
      soif(100),
      humeur(100),
      empoisonnement(0),
      estMort(false),
      nom(nom),
      type(type),
      etat(EtatAnimal::Normal)
{
    qDebug() << "[Animal] Créé:" << nom << "de type" << type;
    
    // Initialisation des timers
    timerDecroissance = new QTimer(this);
    connect(timerDecroissance, &QTimer::timeout, this, &Animal::decroissance);
    timerDecroissance->start(5000); // Toutes les 5 secondes
    
    timerEmpoisonnement = new QTimer(this);
    connect(timerEmpoisonnement, &QTimer::timeout, this, &Animal::verifierEtat);
    timerEmpoisonnement->start(2000); // Toutes les 2 secondes
    
    // Initialisation de la chaîne de responsabilité
    effectChain = new FaimHandler(this);
    auto soifHandler = new SoifHandler(this);
    auto humeurHandler = new HumeurHandler(this);
    auto empoisonnementHandler = new EmpoisonnementHandler(this);
    
    effectChain->setNext(soifHandler);
    soifHandler->setNext(humeurHandler);
    humeurHandler->setNext(empoisonnementHandler);
    
    qDebug() << "[Animal] Chaîne d'effets initialisée";
}

Animal::~Animal()
{
    qDebug() << "[Animal] Détruit:" << nom;
}

QString Animal::getEtatString() const
{
    switch (etat) {
        case EtatAnimal::Normal: return "Normal";
        case EtatAnimal::Affame: return "Affamé";
        case EtatAnimal::Assoiffe: return "Assoiffé";
        case EtatAnimal::Triste: return "Triste";
        case EtatAnimal::Empoisonne: return "Empoisonné";
        case EtatAnimal::Mort: return "Mort";
        default: return "Inconnu";
    }
}

void Animal::donnerAliment(Aliment *aliment)
{
    if (estMort) {
        qDebug() << "[Animal]" << nom << "est mort, ne peut pas manger";
        emit reactionAliment("💀 " + nom + " est mort et ne peut plus manger!");
        return;
    }
    
    if (!aliment) {
        qDebug() << "[Animal] Aliment null";
        return;
    }
    
    qDebug() << "[Animal]" << nom << "reçoit" << aliment->getNom();
    
    // Vérifier si l'animal accepte cet aliment
    if (!accepteAliment(aliment)) {
        qDebug() << "[Animal]" << nom << "refuse" << aliment->getNom();
        emit reactionAliment("❌ " + nom + " refuse " + aliment->getNom());
        return;
    }
    
    // Traiter les effets via la chaîne de responsabilité
    if (effectChain) {
        effectChain->handleEffect(this, aliment);
    }
    
    // Réaction spécifique de l'animal
    reagir(aliment);
    
    // Vérifier l'état après l'aliment
    verifierEtat();
    
    // Émettre le message de réaction
    emit reactionAliment(getReactionMessage(aliment));
}

void Animal::resetAnimal()
{
    qDebug() << "[Animal] Reset de" << nom;
    
    setFaim(100);
    setSoif(100);
    setHumeur(100);
    setEmpoisonnement(0);
    estMort = false;
    emit estMortChanged();
    
    setEtat(EtatAnimal::Normal);
    
    // Redémarrer les timers
    timerDecroissance->start(5000);
    timerEmpoisonnement->start(2000);
    
    emit reactionAliment("✨ " + nom + " a été ressuscité!");
}

void Animal::decroissance()
{
    if (estMort) {
        timerDecroissance->stop();
        return;
    }
    
    qDebug() << "[Animal] Décroissance pour" << nom;
    
    setFaim(faim - getDecroissanceFaim());
    setSoif(soif - getDecroissanceSoif());
    setHumeur(humeur - getDecroissanceHumeur());
    
    // Diminuer l'empoisonnement naturellement
    if (empoisonnement > 0) {
        setEmpoisonnement(empoisonnement - getDecroissanceEmpoisonnement());
    }
    
    verifierEtat();
}

void Animal::verifierEtat()
{
    if (estMort) return;
    
    EtatAnimal nouvelEtat = EtatAnimal::Normal;
    
    // Vérifier la mort
    if (faim <= 0 || soif <= 0 || empoisonnement >= 100) {
        nouvelEtat = EtatAnimal::Mort;
    }
    // Vérifier l'empoisonnement
    else if (empoisonnement >= 50) {
        nouvelEtat = EtatAnimal::Empoisonne;
    }
    // Vérifier la faim
    else if (faim <= 20) {
        nouvelEtat = EtatAnimal::Affame;
    }
    // Vérifier la soif
    else if (soif <= 20) {
        nouvelEtat = EtatAnimal::Assoiffe;
    }
    // Vérifier la tristesse
    else if (humeur <= 20) {
        nouvelEtat = EtatAnimal::Triste;
    }
    
    if (nouvelEtat != etat) {
        setEtat(nouvelEtat);
        
        if (nouvelEtat == EtatAnimal::Mort) {
            mourir();
        }
    }
}

void Animal::setFaim(int valeur)
{
    int nouvelleValeur = qBound(0, valeur, 100);
    if (faim != nouvelleValeur) {
        faim = nouvelleValeur;
        emit faimChanged();
    }
}

void Animal::setSoif(int valeur)
{
    int nouvelleValeur = qBound(0, valeur, 100);
    if (soif != nouvelleValeur) {
        soif = nouvelleValeur;
        emit soifChanged();
    }
}

void Animal::setHumeur(int valeur)
{
    int nouvelleValeur = qBound(0, valeur, 100);
    if (humeur != nouvelleValeur) {
        humeur = nouvelleValeur;
        emit humeurChanged();
    }
}

void Animal::setEmpoisonnement(int valeur)
{
    int nouvelleValeur = qBound(0, valeur, 100);
    if (empoisonnement != nouvelleValeur) {
        empoisonnement = nouvelleValeur;
        emit empoisonnementChanged();
    }
}

void Animal::setEtat(EtatAnimal nouvelEtat)
{
    if (etat != nouvelEtat) {
        EtatAnimal ancienEtat = etat;
        etat = nouvelEtat;
        
        qDebug() << "[Animal]" << nom << "passe de" << static_cast<int>(ancienEtat) 
                 << "à" << static_cast<int>(nouvelEtat);
        
        emit etatChanged();
        onEtatChanged(nouvelEtat);
    }
}

void Animal::mourir()
{
    if (!estMort) {
        estMort = true;
        
        qDebug() << "[Animal]" << nom << "est mort! 💀";
        
        // Arrêter les timers
        timerDecroissance->stop();
        timerEmpoisonnement->stop();
        
        emit estMortChanged();
        emit animalMort();
        emit reactionAliment("💀 " + nom + " est mort!");
        
        onMort();
    }
}

void Animal::appliquerEffetFaim(int valeur)
{
    setFaim(getFaim() + valeur);
}

void Animal::appliquerEffetSoif(int valeur)
{
    setSoif(getSoif() + valeur);
}

void Animal::appliquerEffetHumeur(int valeur)
{
    setHumeur(getHumeur() + valeur);
}

void Animal::appliquerEffetEmpoisonnement(int valeur)
{
    setEmpoisonnement(getEmpoisonnement() + valeur);
}
