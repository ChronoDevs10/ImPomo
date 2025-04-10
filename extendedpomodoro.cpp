#include "extendedpomodoro.h"

void ExtendedPomodoro::start() {}
void ExtendedPomodoro::pause() {}
void ExtendedPomodoro::reset() {}
void ExtendedPomodoro::nextPhase() {}
PomodoroTask ExtendedPomodoro::getcurrent() {
    PomodoroTask task("", 0);
    return task;
}
void ExtendedPomodoro::saveSessionStateToFile() {}
void ExtendedPomodoro::loadSessionStateFromFile() {}
void ExtendedPomodoro::update() {}
void ExtendedPomodoro::reorderTasks(QVector<PomodoroTask*> newOrder) {}
