#include "classicpomodoro.h"

void ClassicPomodoro::start() {}
void ClassicPomodoro::pause() {}
void ClassicPomodoro::reset() {}
void ClassicPomodoro::nextPhase() {}
int ClassicPomodoro::getWorkDuration() {
    return -1;
}
int ClassicPomodoro::getShortBreakDuration() {
    return -1;
}
int ClassicPomodoro::getLongBreakDuration() {
    return -1;
}
int ClassicPomodoro::getCycles() {
    return -1;
}
QString ClassicPomodoro::getcurrentPhase() {
    return "Work";
}
void ClassicPomodoro::saveSessionStateToFile() {}
void ClassicPomodoro::loadSessionStateFromFile() {}
void ClassicPomodoro::changeProperties(int newWork, int newShortBreak, int newLongBreak, int newCycles) {}
void ClassicPomodoro::update() {}
void ClassicPomodoro::loadSettingsFromFile() {}
void ClassicPomodoro::saveSettingsToFile() {}

