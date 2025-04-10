#ifndef ITASKLIST_H
#define ITASKLIST_H
#pragma once

#include "Task.h"
#include <QVector>

class ITaskList {
public:
    virtual void addTask(Task* task) = 0;
    virtual void removeTask(Task* task) = 0;
    virtual void editTaskName(Task* task, QString newName) = 0;
    virtual void editTaskStatus() = 0;
    virtual void reorderTasks(QVector<Task*> newOrder) = 0;
    virtual void saveToDatabase() = 0;
    virtual void updateInDatabase(Task* task) = 0;
    virtual void loadFromDatabase() = 0;
};

#endif // ITASKLIST_H
