#include "toDoList.h"

void ToDoList::addTask(Task* task) {}
void ToDoList::removeTask(Task* task) {}
void ToDoList::editTaskName(Task* task, QString newName) {}
void ToDoList::editTaskStatus(Task* task) {}
int ToDoList::taskCount() {
    return -1;
}
QVector<Task*> ToDoList::getTasks() {
    return {};
}
void ToDoList::reorderTasks(QVector<Task*> newOrder) {}
void ToDoList::saveToDatabase() {}
void ToDoList::updateInDatabase(Task* task) {}
void ToDoList::loadFromDatabase() {}
