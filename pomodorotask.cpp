#include "pomodoroTask.h"

PomodoroTask::PomodoroTask(QString name, int duration) : Task(name), duration(duration) {}

int PomodoroTask::getDuration() {
    return duration;
}

void PomodoroTask::editDuration(int newDuration) {
    if(newDuration >= 0)
        duration = newDuration;
    else
        duration = 0;
}
