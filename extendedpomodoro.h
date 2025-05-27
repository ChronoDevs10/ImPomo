#ifndef EXTENDEDPOMODORO_H
#define EXTENDEDPOMODORO_H

#include "ipomodoromode.h"
#include "pomodorolist.h"
#include "pomodorotask.h"
#include "timer.h"
#include "itimerobserver.h"
#include "notifications.h"
#include "appsettings.h"
#include "notifications.h"
#include "statistics.h"

class ExtendedPomodoro: public QObject, public IPomodoroMode, public ITimerObserver  {
    Q_OBJECT
private:
    int current;
public:
    PomodoroList* list;
    Timer* timer;
    QLabel* currTaskLabel;
    int tasksFinished;
    bool wasStarted;
    AppSettings* settings;
    Notifications* notifications;
    Statistics* stats;

    ExtendedPomodoro();
    ExtendedPomodoro(PomodoroList* List);
    void start() override;
    void pause() override;
    void reset() override;
    void nextPhase() override;
    void update() override;

    void saveSessionStateToFile() override;
    void loadSessionStateFromFile() override;
    void loadFromDatabase();

    int getcurrent();
    void setcurrent(int newCurr);
    void updateCurrentTaskLabel();
    void reorderTasks();
    void clearAllTasks();
    void changeStyle();
};

#endif // EXTENDEDPOMODORO_H
