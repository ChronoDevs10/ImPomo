#include "taskfactory.h"

Task* TaskFactory::createTask(QString taskType, QString name, int duration) {
    return new Task("");
}
