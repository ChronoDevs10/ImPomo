#include "task.h"

Task::Task(QString taskName) : name(taskName), isCompleted(false) {}
void Task::editStatus() {
    isCompleted = !isCompleted;
}
void Task::editName(QString newName) {
    if(name == " ")
        name = "Task";
    else
        name = newName;
}
bool Task::getStatus() {
    return isCompleted;
}
QString Task::getName() {
    return name;
}
