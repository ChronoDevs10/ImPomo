#ifndef TODOLIST_H
#define TODOLIST_H

#include "ITaskList.h"

class ToDoList : public ITaskList {
private:
    QVector<Task*> tasks;
public:
    void addTask(Task* task) override;
    void removeTask(Task* task) override;
    void editTaskName(Task* task, QString newName) override;
    void editTaskStatus() override;
    void reorderTasks(QVector<Task*> newOrder) override;
    void saveToDatabase() override;
    void updateInDatabase(Task* task) override;
    void loadFromDatabase() override;
};
#endif // TODOLIST_H
