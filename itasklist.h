#ifndef ITASKLIST_H
#define ITASKLIST_H
#pragma once

#include "task.h"
#include "pomodorotask.h"
#include <QVector>

class ITaskList {
public:
    virtual void addTask(Task* task) = 0;
    virtual void removeTask(Task* task) = 0;
    virtual void editTaskName(Task* task, QString newName) = 0;
    virtual void editTaskStatus(Task* task) = 0;
    virtual int taskCount() = 0;
    virtual void reorderTasks(int, int) = 0;
    virtual void saveToDatabase() = 0;
    virtual void updateInDatabase(Task* task) = 0;
    virtual void loadFromDatabase() = 0;
};

#endif // ITASKLIST_H
