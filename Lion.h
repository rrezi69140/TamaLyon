#ifndef LION_H
#define LION_H


#include <QObject>
#include <QString>
class LionManager : public QObject {

    Q_OBJECT

     Q_PROPERTY(QString mood READ mood WRITE setMood NOTIFY moodChanged)


private:
    QString m_mood =  "Triste" ;
public:
    explicit LionManager(QObject *parent = nullptr);
      QString mood() const;

    void setMood (const QString &newMood);

signals:
    void moodChanged();

public slots:
    void onMoodChange();
};

#endif // LION_H





