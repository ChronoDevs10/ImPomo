#ifndef STATISTICS_H
#define STATISTICS_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include "appsettings.h"

class Statistics {
public:
    AppSettings* appSettings;

    Statistics();
    void addImpomoData(int timeSpent);
    void addClassicPomodoroData(int timeSpent);
    int getDailyTimeImpomo(QString date);
    int getDailyTimePomodoro(QString date);
    int getDailyTasksNumber(QString date);
    void displayReport(const QDate& date);
    void databaseInit();
};

#endif // STATISTICS_H
