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
    Timer timer;
    void start() override;
    void pause() override;
    void reset() override;
    void nextPhase() override;
    void saveSessionStateToFile() override;
    void loadSessionStateFromFile() override;
    void update() override;

    PomodoroTask getcurrent();
    void reorderTasks(QVector<PomodoroTask*> newOrder);
};

#endif // EXTENDEDPOMODORO_H
