#include "pomodoroTask.h"

PomodoroTask::PomodoroTask(QString name, int duration) : Task(name), duration(duration) {}

void PomodoroTask::editStatus()  {}

void PomodoroTask::editName(QString newName)  {}

bool PomodoroTask::getStatus() {
    return true;
}

QString PomodoroTask::getName()  {
    return "";
}

int PomodoroTask::getDuration() {
    return -1110;
}

void PomodoroTask::editDuration(int newDuration) {}
