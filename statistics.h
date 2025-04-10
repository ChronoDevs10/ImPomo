#ifndef STATISTICS_H
#define STATISTICS_H

#include <QVector>
#include <QString>
#include <QMap>
#include "task.h"

class Statistics {
private:
    QMap<QString, QVector<Task*>> completedTasksByDay;
    QMap<QString, int> dailyTimeWorked;
public:
    void addCompletedTaskForDay(Task* task, int timeSpent, QString date);
    void addClassicPomodoroTime(QString date, int time);
    int getDailyTimeWorked(QString date);
    QVector<Task*> getCompletedTasksForDay(QString date);
    void loadFromFile();
    void saveToFile();
    void displayReport(QString date);
};

#endif // STATISTICS_H
