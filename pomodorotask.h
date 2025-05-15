#ifndef POMODOROTASK_H
#define POMODOROTASK_H

#include "task.h"
#include <QLineEdit>

class PomodoroTask : public Task {
private:
    int duration;
public:
    PomodoroTask(QString name, int duration);
    QLineEdit* lineEdit;

    int getDuration();
    void editDuration(int newDuration);
};
#endif
