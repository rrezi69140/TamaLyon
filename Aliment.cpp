#include "Aliment.h"
#include <QDebug>

Aliment::Aliment(QObject *parent)
    : QObject(parent),
      faimImpact(0),
      soifImpact(0),
      humeurImpact(0),
      estToxique(false),
      categorie("unknown"),
      nom("Aliment"),
      emoji("🍽️")
{
    qDebug() << "[Aliment] Créé:" << nom;
}
