#include "EffectHandler.h"
#include "Animal.h"
#include <QDebug>

// ========================================
// EffectHandler (Base)
// ========================================

EffectHandler::EffectHandler(QObject *parent)
    : QObject(parent), nextHandler(nullptr)
{
}

void EffectHandler::setNext(EffectHandler *handler)
{
    nextHandler = handler;
}

void EffectHandler::handleEffect(Animal *animal, Aliment *aliment)
{
    if (animal && aliment) {
        qDebug() << "[EffectHandler]" << getEffectName() << "traite" << aliment->getNom();
        processEffect(animal, aliment);
        
        if (nextHandler) {
            nextHandler->handleEffect(animal, aliment);
        }
    }
}

// ========================================
// FaimHandler
// ========================================

FaimHandler::FaimHandler(QObject *parent)
    : EffectHandler(parent)
{
}

void FaimHandler::processEffect(Animal *animal, Aliment *aliment)
{
    if (aliment->getFaimImpact() != 0) {
        qDebug() << "[FaimHandler]" << aliment->getNom() 
                 << "impact faim:" << aliment->getFaimImpact();
        
        animal->appliquerEffetFaim(aliment->getFaimImpact());
    }
}

// ========================================
// SoifHandler
// ========================================

SoifHandler::SoifHandler(QObject *parent)
    : EffectHandler(parent)
{
}

void SoifHandler::processEffect(Animal *animal, Aliment *aliment)
{
    if (aliment->getSoifImpact() != 0) {
        qDebug() << "[SoifHandler]" << aliment->getNom() 
                 << "impact soif:" << aliment->getSoifImpact();
        
        animal->appliquerEffetSoif(aliment->getSoifImpact());
    }
}

// ========================================
// HumeurHandler
// ========================================

HumeurHandler::HumeurHandler(QObject *parent)
    : EffectHandler(parent)
{
}

void HumeurHandler::processEffect(Animal *animal, Aliment *aliment)
{
    if (aliment->getHumeurImpact() != 0) {
        qDebug() << "[HumeurHandler]" << aliment->getNom() 
                 << "impact humeur:" << aliment->getHumeurImpact();
        
        animal->appliquerEffetHumeur(aliment->getHumeurImpact());
    }
}

// ========================================
// EmpoisonnementHandler
// ========================================

EmpoisonnementHandler::EmpoisonnementHandler(QObject *parent)
    : EffectHandler(parent)
{
}

void EmpoisonnementHandler::processEffect(Animal *animal, Aliment *aliment)
{
    if (aliment->getEstToxique()) {
        qDebug() << "[EmpoisonnementHandler]" << aliment->getNom() 
                 << "est toxique! Niveau empoisonnement:" << aliment->getEmpoisonnementLevel();
        
        animal->appliquerEffetEmpoisonnement(aliment->getEmpoisonnementLevel());
    }
}
