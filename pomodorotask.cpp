#include "pomodoroTask.h"

PomodoroTask::PomodoroTask(QString name, int duration) : Task(name), duration(duration) {}
/*
void PomodoroTask::editStatus()  {
    isCompleted = !isCompleted;
}

void PomodoroTask::editName(QString newName)  {
    name = newName;
}
bool PomodoroTask::getStatus() {
    return true;
}
QString PomodoroTask::getName()  {
    return "";
}
*/
int PomodoroTask::getDuration() {
    return duration;
}

void PomodoroTask::editDuration(int newDuration) {
    if(newDuration >= 0)
        duration = newDuration;
    else
        duration = 0;
}
