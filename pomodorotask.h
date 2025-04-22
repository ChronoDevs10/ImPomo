#ifndef POMODOROTASK_H
#define POMODOROTASK_H

#include "task.h"

class PomodoroTask : public Task {
private:
    int duration;
public:
    PomodoroTask(QString name, int duration);
    //void editStatus() override;
    //void editName(QString newName) override;
    //bool getStatus() override;
    //QString getName() override;

    int getDuration();
    void editDuration(int newDuration);
};
#endif
