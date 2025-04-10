#include "pomodorolist.h"

void PomodoroList::addTask(Task* task) {}
void PomodoroList::removeTask(Task* task) {}
void PomodoroList::editTaskName(Task* task, QString newName) {}
void PomodoroList::editTaskStatus(Task* task) {}
int PomodoroList::taskCount() {
    return -1;
}
QVector<PomodoroTask*> PomodoroList::getPTasks() {
    return {};
}
void PomodoroList::reorderTasks(QVector<Task*> newOrder) {}
void PomodoroList::saveToDatabase() {}
void PomodoroList::updateInDatabase(Task* task) {}
void PomodoroList::loadFromDatabase() {}
void PomodoroList::editTaskDuration(Task* task, int newDuration) {}
