#ifndef TASK_H
#define TASK_H

#include <QString>

class Task {
private:
    QString name;
    bool isCompleted;
public:
    Task(QString name);
    virtual void editStatus();
    virtual void editName(QString newName);
    virtual bool getStatus();
    virtual QString getName();
};

#endif // TASK_H
