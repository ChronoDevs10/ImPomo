#ifndef POMODOROLIST_H
#define POMODOROLIST_H

#include "ITaskList.h"
#include "pomodorotask.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>

class PomodoroList : public ITaskList {
private:
    QVector<PomodoroTask*> tasks;
public:
    void addTask(Task* task) override;
    void removeTask(Task* task) override;
    void editTaskName(Task* task, QString newName) override;
    void editTaskStatus(Task* task) override;
    int taskCount() override;
    QVector<PomodoroTask*> getPTasks();
    void reorderTasks(int, int) override;
    void saveToDatabase() override;
    void updateInDatabase(Task* task) override;
    void loadFromDatabase() override;

    void editTaskDuration(Task* task, int newDuration);

    QWidget* createTaskWidget(PomodoroTask* task);
    void refreshList(QVBoxLayout* layout);
    QScrollArea* getScrollArea();
};

#endif // POMODOROLIST_H
