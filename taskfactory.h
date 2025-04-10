#ifndef TASKFACTORY_H
#define TASKFACTORY_H

#include "task.h"
#include "pomodoroTask.h"

class TaskFactory {
public:
    static Task* createTask(QString taskType, QString name, int duration = 0);
};

#endif // TASKFACTORY_H
