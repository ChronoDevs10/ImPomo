#ifndef CLASSICPOMODORO_H
#define CLASSICPOMODORO_H

#include <Qstring>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include "ipomodoromode.h"
#include "timer.h"
#include "itimerobserver.h"
#include "appsettings.h"
#include "notifications.h"
#include "statistics.h"

class ClassicPomodoro : public IPomodoroMode, public ITimerObserver {
private:
    int workDuration;
    int shortBreakDuration;
    int longBreakDuration;
    int cycles;
    int workBlocksInCycle;
    int currentWorkBlock;
    int currentCycle;
    QString currentPhase;
public:
    AppSettings* settings;
    Notifications* notifications;
    Statistics* stats;
    Timer* timer;
    QLabel* phaseLabel;

    ClassicPomodoro();
    void start() override;
    void pause() override;
    void reset() override;
    void nextPhase() override;
    void saveSessionStateToFile() override;
    void loadSessionStateFromFile() override;
    void update() override;

    void changeProperties(int newWork, int newShortBreak, int newLongBreak, int newCycles, int workBlocks);
    void setCurrentPhase(QString newPhase);
    int getWorkDuration();
    int getShortBreakDuration();
    int getLongBreakDuration();
    int getCycles();
    int getWorkBlocks();
    QString getcurrentPhase();
    void changeStyle();

    void loadSettingsFromFile();
    void saveSettingsToFile();
};

#endif // CLASSICPOMODORO_H
