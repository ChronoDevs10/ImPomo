#ifndef EXTENDEDPOMODORO_H
#define EXTENDEDPOMODORO_H

#include "ipomodoromode.h"
#include "pomodorolist.h"
#include "pomodorotask.h"
#include "timer.h"
#include "itimerobserver.h"

class ExtendedPomodoro : public IPomodoroMode, public ITimerObserver {
private:
    PomodoroTask* current;
public:
    PomodoroList* list;
    Timer* timer;
    QLabel* currTaskLabel;

    ExtendedPomodoro();
    ExtendedPomodoro(PomodoroList* List);
    void start() override;
    void pause() override;
    void reset() override;
    void nextPhase() override;
    void update() override;

    void saveSessionStateToFile() override;
    void loadSessionStateFromFile() override;

    PomodoroTask* getcurrent();
    void setcurrent(PomodoroTask* newCurr);
    void reorderTasks();
};

#endif // EXTENDEDPOMODORO_H
