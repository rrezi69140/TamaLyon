#include "Lion.h"
#include <QDebug>

LionManager::LionManager(QObject *parent):
    QObject(parent),m_mood("Triste"){}


 QString LionManager::mood() const {
    return m_mood;
}



void LionManager::setMood(const QString &newMood) {
    if (m_mood != newMood) {
        m_mood = newMood;
        emit moodChanged();
    }
}


void LionManager::onMoodChange() {
    // Ton code ici (ex: debug ou logique)
    qDebug() << "Mood changed to:" << m_mood;
}


