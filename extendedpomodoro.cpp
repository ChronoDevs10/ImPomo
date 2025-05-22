#include "extendedpomodoro.h"
#include <QDebug>

ExtendedPomodoro::ExtendedPomodoro() {
    current = 0;
    list = nullptr;
    tasksFinished = 0;

    timer = new Timer();
    timer->setSubscriber(this);
    currTaskLabel = new QLabel("No tasks on the list");
}

ExtendedPomodoro::ExtendedPomodoro(PomodoroList* List) {
    list = List;
    list->parent = this;
    tasksFinished = 0;

    timer = new Timer();
    timer->setSubscriber(this);

    if(list->taskCount() == 0) {
        current = 0;
        currTaskLabel = new QLabel("No tasks on the list");
    }
    else {
        current = 0;
        timer->setTime(list->getPTasks().at(0)->getDuration());
        currTaskLabel = new QLabel("Current task: " + list->getPTasks().at(0)->getName());
    }
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
    if(list->taskCount() == tasksFinished)
        return;

    list->getPTasks().at(current)->lineEdit->setStyleSheet( "background-color: #a7a7a7; border: 1px solid #4c4c4c; "
    "border-radius: 5px; padding: 5px; color: black; text-decoration: line-through;");
    list->editTaskStatus(list->getPTasks().at(current), true);

    if(current < (list->taskCount() - 1)){
        current++;
        timer->setTime(list->getPTasks().at(current)->getDuration());
        currTaskLabel->setText("Current task: " + list->getPTasks().at(current)->getName());
        start();
    }
    else {
        tasksFinished = list->taskCount();
        currTaskLabel->setText("All tasks finished");
        pause();
    }
}
int ExtendedPomodoro::getcurrent() {
    return current;
}
void ExtendedPomodoro::setcurrent(int newCurr) {
    current = newCurr;
}
void ExtendedPomodoro::update() {
    wasStarted = true;
    nextPhase();
    notifications->playSound();
}
void ExtendedPomodoro::reorderTasks() {}
void ExtendedPomodoro::updateCurrentTaskLabel() {
    if(list->taskCount() > 0) {
        QString taskName = list->getPTasks().at(current)->getName();
        currTaskLabel->setText("Current task: " + taskName);
    } else
        currTaskLabel->setText("No tasks on the list");
}
void ExtendedPomodoro::clearAllTasks() {
    for(int i = list->taskCount() - 1; i >= 0; i--) {
        PomodoroTask* task = list->getPTasks().at(i);
        list->removeTask(task);
        delete task;
    }

    current = 0;
    tasksFinished = 0;
    wasStarted = false;
    pause();
    timer->setTime(0);
    currTaskLabel->setText("No tasks on the list");
}


void ExtendedPomodoro::saveSessionStateToFile() {}
void ExtendedPomodoro::loadSessionStateFromFile() {}

