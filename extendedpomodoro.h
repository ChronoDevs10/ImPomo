#ifndef EXTENDEDPOMODORO_H
#define EXTENDEDPOMODORO_H

#include "ipomodoromode.h"
#include "pomodorolist.h"
#include "pomodorotask.h"
#include "timer.h"
#include "itimerobserver.h"

class ExtendedPomodoro : public IPomodoroMode, public ITimerObserver {
private:
    PomodoroList* list;
    PomodoroTask current;
    Timer timer;
public:
    void start() override;
    void pause() override;
    void reset() override;
    void nextPhase() override;
    void saveSessionStateToFile() override;
    void loadSessionStateFromFile() override;
    void update() override;

    void reorderTasks(QVector<PomodoroTask*> newOrder);
};

#endif // EXTENDEDPOMODORO_H
