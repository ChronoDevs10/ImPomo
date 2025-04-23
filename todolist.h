#ifndef TODOLIST_H
#define TODOLIST_H

#include "ITaskList.h"
#include <QVector>
#include <QListWidget>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QScrollArea>

class ToDoList : public ITaskList {
private:
    QVector<Task*> tasks;

public:
    ToDoList();

    void addTask(Task* task) override;
    void removeTask(Task* task) override;
    void editTaskName(Task* task, QString newName) override;
    void editTaskStatus(Task* task) override;
    int taskCount() override;
    QVector<Task*> getTasks();
    void reorderTasks(QVector<Task*> newOrder) override;
    void saveToDatabase() override;
    void updateInDatabase(Task* task) override;
    void loadFromDatabase() override;

    QWidget* createTaskWidget(Task* task);
    void refreshListIn(QVBoxLayout* layout);
    QScrollArea* getScrollArea();
};

#endif // TODOLIST_H
