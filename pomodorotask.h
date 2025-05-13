#ifndef POMODOROTASK_H
#define POMODOROTASK_H

#include "task.h"

class PomodoroTask : public Task {
private:
    int duration;
public:
    PomodoroTask(QString name, int duration);

    int getDuration();
    void editDuration(int newDuration);
};
#endif
