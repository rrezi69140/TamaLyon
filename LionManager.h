#ifndef LIONMANAGER_H
#define LIONMANAGER_H

#include <QObject>
#include <QString>
#include <QTimer>

class LionManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString mood READ mood WRITE setMood NOTIFY moodChanged)

public:
    explicit LionManager(QObject *parent = nullptr);

    QString mood() const;
    void setMood(const QString &newMood);

    void feed(int points);
    void giveWater(int points);
    void pet(int points);

    QString generateStateMessage() const;

signals:
    void moodChanged();
    void stateUpdated(const QString &state);

private slots:
    void decayStates();

private:
    QString m_mood;
    int hunger;
    int thirst;
    int affection;
    QTimer decayTimer;

    void updateMood();
};

#endif // LIONMANAGER_H
