#include "extendedpomodoro.h"
#include <QDebug>

ExtendedPomodoro::ExtendedPomodoro() {
    current = 0;
    list = nullptr;

    timer = new Timer();
    timer->setSubscriber(this);
    timer->type = 1;
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
        current = 0;//ostatnio zapisany indeks
        currTaskLabel = new QLabel("Current task: " + list->getPTasks().at(0)->getName());
    }
    currTaskLabel->setStyleSheet("font-size: 25px; font-weight: bold; margin: 10px;");

    timer = new Timer();
    timer->setSubscriber(this);
    timer->type = 1;
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
    list->getPTasks().at(current)->lineEdit->setStyleSheet(
        "QLineEdit {"
        "   font-size: 16px;"
        "   background-color: #ccc;"
        "   border: 1px solid #ccc;"
        "   border-right: 1px solid #999;"
        "   border-top-left-radius: 5px;"
        "   border-bottom-left-radius: 5px;"
        "   padding: 5px 10px;"
        "   color: black;"
        "   text-decoration: line-through;"
        "}"
    );

    if(current < (list->taskCount() - 1)){
        list->getPTasks().at(current)->editStatus();
        current++;
        timer->setTime(list->getPTasks().at(current)->getDuration());
        currTaskLabel->setText("Current task: " + list->getPTasks().at(current)->getName());
        start();
    }
    else {
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
    nextPhase();
}
void ExtendedPomodoro::reorderTasks() {}
void ExtendedPomodoro::updateCurrentTaskLabel() {
    if(list->taskCount() > 0) {
        QString taskName = list->getPTasks().at(current)->getName();
        currTaskLabel->setText("Current task: " + taskName);
    } else
        currTaskLabel->setText("No tasks on the list");
}

void ExtendedPomodoro::saveSessionStateToFile() {}
void ExtendedPomodoro::loadSessionStateFromFile() {}

