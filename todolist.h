#ifndef TODOLIST_H
#define TODOLIST_H

#include "ITaskList.h"
#include "appsettings.h"
#include <QVector>
#include <QListWidget>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QScrollArea>

class ToDoList : public ITaskList {
private:
    QVector<Task*> tasks;

public:
    AppSettings* settings;
    ToDoList();

    void addTask(Task* task) override;
    void removeTask(Task* task) override;
    void editTaskName(Task* task, QString newName) override;
    void editTaskStatus(Task* task) override;
    int taskCount() override;
    QVector<Task*> getTasks();
    void reorderTasks(int, int) override;
    void changeStyle();

    void saveToDatabase() override;
    void updateInDatabase(Task* task) override;
    void loadFromDatabase() override;

    QWidget* createTaskWidget(Task* task);
    void refreshList(QVBoxLayout* layout);
    QScrollArea* getScrollArea();
};

#endif // TODOLIST_H
