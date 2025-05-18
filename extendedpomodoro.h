#ifndef EXTENDEDPOMODORO_H
#define EXTENDEDPOMODORO_H

#include "ipomodoromode.h"
#include "pomodorolist.h"
#include "pomodorotask.h"
#include "timer.h"
#include "itimerobserver.h"

class ExtendedPomodoro: public IPomodoroMode, public ITimerObserver  {
private:
    int current;
public:
    PomodoroList* list;
    Timer* timer;
    QLabel* currTaskLabel;
    int tasksFinished;
    bool wasStarted;

    ExtendedPomodoro();
    ExtendedPomodoro(PomodoroList* List);
    void start() override;
    void pause() override;
    void reset() override;
    void nextPhase() override;
    void update() override;

    void saveSessionStateToFile() override;
    void loadSessionStateFromFile() override;

    int getcurrent();
    void setcurrent(int newCurr);
    void updateCurrentTaskLabel();
    void reorderTasks();
    void clearAllTasks();
};

#endif // EXTENDEDPOMODORO_H
