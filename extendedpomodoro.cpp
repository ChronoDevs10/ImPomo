#include "extendedpomodoro.h"

ExtendedPomodoro::ExtendedPomodoro() {
    current = nullptr;
    list = nullptr;

    timer = new Timer();
    timer->setSubscriber(this);
    currTaskLabel = new QLabel("No tasks on the list");
}

ExtendedPomodoro::ExtendedPomodoro(PomodoroList* List) {
    list = List;
    list->parent = this;

    if(list->taskCount() == 0) {
        current = nullptr;
        currTaskLabel = new QLabel("No tasks on the list");
    }
    else{ //pod ładowanie z bazy danych
        current = list->getPTasks().at(0);
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
void ExtendedPomodoro::updateCurrentTaskLabel() {
    if(list->taskCount() > 0) {
        currTaskLabel->setText("Current task: " + list->getPTasks().at(0)->getName());
    } else {
        currTaskLabel->setText("No tasks on the list");
    }
}


void ExtendedPomodoro::saveSessionStateToFile() {}
void ExtendedPomodoro::loadSessionStateFromFile() {}

