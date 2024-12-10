#ifndef TUTORIALS_H
#define TUTORIALS_H

#include <QStringList>
#include <QString>
#include <QMovie>

class Tutorials
{
public:
    Tutorials();

    QMovie* getExerciseGif(int index) const;
    QString getExerciseDescription(int index) const;
    QStringList getExerciseNames() const;

private:
    QStringList exerciseNames;
    QList<QMovie*> exerciseGifs;
    QStringList exerciseDescriptions;

    void loadExercises();
};

#endif // TUTORIALS_H
