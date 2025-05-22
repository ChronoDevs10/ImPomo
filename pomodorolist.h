#ifndef POMODOROLIST_H
#define POMODOROLIST_H

#include "ITaskList.h"
#include "pomodorotask.h"
#include "appsettings.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>

class ExtendedPomodoro;

class PomodoroList : public ITaskList {
private:
    QVector<PomodoroTask*> tasks;

public:
    ExtendedPomodoro* parent;
    AppSettings* settings;

    PomodoroList();
    void addTask(Task* task) override;
    void removeTask(Task* task) override;
    void editTaskName(Task* task, QString newName) override;
    void editTaskStatus(Task* task, bool status) override;
    int taskCount() override;
    QVector<PomodoroTask*> getPTasks();
    void reorderTasks(int, int) override;

    void saveToDatabase() override;
    void loadFromDatabase() override;
    void databaseInit();

    void editTaskDuration(Task* task, int newDuration);

    QWidget* createTaskWidget(PomodoroTask* task);
    void refreshList(QVBoxLayout* layout);
    QScrollArea* getScrollArea();
};

#endif // POMODOROLIST_H
