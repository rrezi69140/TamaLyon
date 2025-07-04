#include "LionManager.h"
#include <QDebug>

LionManager::LionManager(QObject *parent)
    : QObject(parent),
    m_mood("joyeux"),
    hunger(100),
    thirst(100),
    affection(100)
{
    decayTimer.setInterval(5000); // toutes les 5 secondes
    connect(&decayTimer, &QTimer::timeout, this, &LionManager::decayStates);
    decayTimer.start();
    updateMood();
}

QString LionManager::mood() const {
    return m_mood;
}

void LionManager::setMood(const QString &newMood) {
    if (m_mood != newMood) {
        m_mood = newMood;
        emit moodChanged();
        qDebug() << "[LionManager] Mood changé en:" << m_mood;
    }
}

void LionManager::feed(int points) {
    hunger = qMin(hunger + points, 100);
    qDebug() << "[LionManager] Nourri +" << points << "=> Hunger:" << hunger;
    updateMood();
}

void LionManager::giveWater(int points) {
    thirst = qMin(thirst + points, 100);
    qDebug() << "[LionManager] Bu +" << points << "=> Thirst:" << thirst;
    updateMood();
}

void LionManager::pet(int points) {
    affection = qMin(affection + points, 100);
    qDebug() << "[LionManager] Caresse +" << points << "=> Affection:" << affection;
    updateMood();
}

void LionManager::decayStates() {
    hunger = qMax(hunger - 5, 0);
    thirst = qMax(thirst - 5, 0);
    affection = qMax(affection - 2, 0);

    qDebug() << "[LionManager] Décroissance | Hunger:" << hunger << "Thirst:" << thirst << "Affection:" << affection;

    updateMood();
}

void LionManager::updateMood() {
    QString newMood;

    if (hunger < 30) {
        newMood = "affame";
    } else if (thirst < 30) {
        newMood = "triste";
    } else if (affection < 30) {
        newMood = "endormi";
    } else {
        newMood = "joyeux";
    }

    setMood(newMood);

    emit stateUpdated(generateStateMessage());
}

QString LionManager::generateStateMessage() const {
    return QString("H:%1 | T:%2 | A:%3 | Mood:%4")
    .arg(hunger)
        .arg(thirst)
        .arg(affection)
        .arg(m_mood);
}
