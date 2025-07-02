#ifndef LION_H
#define LION_H
#endif // LION_H

#include <QObject>

class LionManager : public QObject {

    Q_OBJECT


private:
    QString mood =  "Joyeux" ;
public:
    explicit LionManager(QObject *parent = nullptr);

    void setMood (const QString &newMood);

signals:
    void moodChange();

public slots:
    void onMoodChange();
};







