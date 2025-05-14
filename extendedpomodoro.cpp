#include "extendedpomodoro.h"

ExtendedPomodoro::ExtendedPomodoro() {
    current = nullptr;
    list = nullptr;
    timer = new Timer();
    timer->setSubscriber(this);
}

ExtendedPomodoro::ExtendedPomodoro(PomodoroList* List) {
    list = List;

    if(list->taskCount() == 0) {
        current = nullptr;
        currTaskLabel = new QLabel("Current task: ");
    }
    else {
        current = list->getPTasks()[0];
        currTaskLabel = new QLabel("Current task: " + current->getName());
    }
    currTaskLabel->setStyleSheet("font-size: 25px; font-weight: bold; margin: 10px;");

    timer = new Timer();
    timer->setSubscriber(this);
}

void ExtendedPomodoro::start() {
    timer->start();
}
void ExtendedPomodoro::pause() {
    timer->pause();
}
void ExtendedPomodoro::reset() {
    timer->reset();
}
void ExtendedPomodoro::nextPhase() {}
PomodoroTask* ExtendedPomodoro::getcurrent() {
    return current;
}
void ExtendedPomodoro::setcurrent(PomodoroTask* newCurr) {
    current = newCurr;
}

void ExtendedPomodoro::update() {}
void ExtendedPomodoro::reorderTasks() {}


void ExtendedPomodoro::saveSessionStateToFile() {}
void ExtendedPomodoro::loadSessionStateFromFile() {}

