#include "toDoList.h"

ToDoList::ToDoList() {
    tasks = QVector<Task*>();
}

void ToDoList::addTask(Task* task) {
    tasks.append(task);
}
void ToDoList::removeTask(Task* task) {
    tasks.removeOne(task);
}
void ToDoList::editTaskName(Task* task, QString newName) {
    task->editName(newName);
}
void ToDoList::editTaskStatus(Task* task) {
    task->editStatus();
}
int ToDoList::taskCount() {
    return tasks.size();
}
QVector<Task*> ToDoList::getTasks() {
    return tasks;
}
void ToDoList::reorderTasks(QVector<Task*> newOrder) {}
void ToDoList::saveToDatabase() {}
void ToDoList::updateInDatabase(Task* task) {}
void ToDoList::loadFromDatabase() {}
