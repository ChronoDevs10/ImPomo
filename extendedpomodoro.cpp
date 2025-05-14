#include "extendedpomodoro.h"
#include <QDebug>

ExtendedPomodoro::ExtendedPomodoro() {
    current = 0;
    list = nullptr;

    timer = new Timer();
    timer->setSubscriber(this);
    currTaskLabel = new QLabel("No tasks on the list");
}

ExtendedPomodoro::ExtendedPomodoro(PomodoroList* List) {
    list = List;
    list->parent = this;

    if(list->taskCount() == 0) {
        current = 0;
        currTaskLabel = new QLabel("No tasks on the list");
    }
    else{ //pod ładowanie z bazy danych
        current = 0;
        currTaskLabel = new QLabel("Current task: " + list->getPTasks().at(0)->getName());
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
void ExtendedPomodoro::nextPhase() {
    if(current < (list->taskCount() - 1)){
        current++;
        timer->setTime(list->getPTasks().at(current)->getDuration());
        currTaskLabel->setText("Current task: " + list->getPTasks().at(current)->getName());
        start();
    }
    else {
        currTaskLabel->setText("All tasks finished");
    }
}
int ExtendedPomodoro::getcurrent() {
    return current;
}
void ExtendedPomodoro::setcurrent(int newCurr) {
    current = newCurr;
}

void ExtendedPomodoro::update() {
    nextPhase();
}
void ExtendedPomodoro::reorderTasks() {}
void ExtendedPomodoro::updateCurrentTaskLabel() {
    if(list->taskCount() > 0) {
        QString taskName = list->getPTasks().at(0)->getName();
        int taskDuration = list->getPTasks().at(0)->getDuration();

        currTaskLabel->setText("Current task: " + taskName);
        timer->setTime(taskDuration);
    } else {
        currTaskLabel->setText("No tasks on the list");
    }
}

void ExtendedPomodoro::saveSessionStateToFile() {}
void ExtendedPomodoro::loadSessionStateFromFile() {}

