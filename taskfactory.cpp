#include "taskfactory.h"

Task* TaskFactory::createTask(QString taskType, QString name, int duration) {
    if(taskType == "Pomodoro")
        return new PomodoroTask(name, duration);
    else
        return new Task(name);
}
