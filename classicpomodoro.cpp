#include "classicpomodoro.h"

void ClassicPomodoro::start() {
    timer->start();
}
void ClassicPomodoro::pause() {
    timer->pause();
}
void ClassicPomodoro::reset() {
    timer->reset();
}
void ClassicPomodoro::nextPhase() {}
int ClassicPomodoro::getWorkDuration() {
    return workDuration;
}
int ClassicPomodoro::getShortBreakDuration() {
    return shortBreakDuration;
}
int ClassicPomodoro::getLongBreakDuration() {
    return longBreakDuration;
}
int ClassicPomodoro::getCycles() {
    return cycles;
}
QString ClassicPomodoro::getcurrentPhase() {
    return currentPhase;
}
void ClassicPomodoro::setCurrentPhase(QString newPhase) {
    currentPhase = newPhase;
}
void ClassicPomodoro::saveSessionStateToFile() {}
void ClassicPomodoro::loadSessionStateFromFile() {}
void ClassicPomodoro::changeProperties(int newWork, int newShortBreak, int newLongBreak, int newCycles) {
    workDuration = newWork;
    shortBreakDuration = newShortBreak;
    longBreakDuration = newLongBreak;
    cycles = newCycles;
}
void ClassicPomodoro::update() {}
void ClassicPomodoro::loadSettingsFromFile() {}
void ClassicPomodoro::saveSettingsToFile() {}

