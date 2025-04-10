#ifndef POMODOROLIST_H
#define POMODOROLIST_H

#include "ITaskList.h"
#include "pomodorotask.h"

class PomodoroList : public ITaskList {
private:
    QVector<PomodoroTask*> tasks;
public:
    void addTask(Task* task) override;
    void removeTask(Task* task) override;
    void editTaskName(Task* task, QString newName) override;
    void editTaskStatus() override;
    void reorderTasks(QVector<Task*> newOrder) override;
    void saveToDatabase() override;
    void updateInDatabase(Task* task) override;
    void loadFromDatabase() override;

    void editTaskDuration(Task* task, int newDuration);
};

#endif // POMODOROLIST_H
