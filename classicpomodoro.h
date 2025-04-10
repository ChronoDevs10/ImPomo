#ifndef CLASSICPOMODORO_H
#define CLASSICPOMODORO_H

#include "ipomodoromode.h"
#include "timer.h"
#include "itimerobserver.h"

class ClassicPomodoro : public IPomodoroMode, public ITimerObserver {
private:
    int workDuration;
    int shortBreakDuration;
    int longBreakDuration;
    int cycles;
    int workBlocksInCycle;
    Timer timer;
public:
    void start() override;
    void pause() override;
    void reset() override;
    void nextPhase() override;
    void saveSessionStateToFile() override;
    void loadSessionStateFromFile() override;
    void update() override;

    void changeProperties(int newWork, int newShortBreak, int newLongBreak, int newCycles);
    void loadSettingsFromFile();
    void saveSettingsToFile();
};


#endif // CLASSICPOMODORO_H
