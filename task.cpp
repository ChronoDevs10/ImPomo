#include "task.h"

Task::Task(QString taskName) : name(taskName), isCompleted(false) {}

void Task::editStatus() {}

void Task::editName(QString newName) {}

bool Task::getStatus()  {
    return false;
}

QString Task::getName()  {
    return "";
}
