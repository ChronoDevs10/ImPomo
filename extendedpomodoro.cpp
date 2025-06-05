#include "extendedpomodoro.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

ExtendedPomodoro::ExtendedPomodoro() {
    current = 0;
    list = nullptr;
    tasksFinished = 0;
    wasStarted = false;

    timer = new Timer();
    timer->setSubscriber(this);
    currTaskLabel = new QLabel("No tasks on the list");

    QObject::connect(timer, &Timer::started, this, [this]() {
        wasStarted = true;
    });
}

ExtendedPomodoro::ExtendedPomodoro(PomodoroList* List) {
    list = List;
    list->parent = this;
    tasksFinished = 0;
    wasStarted = false;

    timer = new Timer();
    timer->setSubscriber(this);

    if(list->taskCount() == 0) {
        current = 0;
        currTaskLabel = new QLabel("No tasks on the list");
    }
    else {
        current = 0;
        timer->setTime(list->getPTasks().at(0)->getDuration()*60);
        currTaskLabel = new QLabel("Current task: " + list->getPTasks().at(0)->getName());
    }

    QObject::connect(timer, &Timer::started, this, [this]() {
        wasStarted = true;
    });
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
        timer->setTime(list->getPTasks().at(current)->getDuration()*60);
        currTaskLabel->setText("Current task: " + list->getPTasks().at(current)->getName());
        start();
    }
    else {
        wasStarted = false;
        timer->setTime(0);
        currTaskLabel->setText("All tasks finished");
        pause();
    }
    tasksFinished++;
    saveSessionStateToFile();
}
int ExtendedPomodoro::getcurrent() {
    return current;
}
void ExtendedPomodoro::setcurrent(int newCurr) {
    current = newCurr;
    saveSessionStateToFile();
}
void ExtendedPomodoro::update() {
    stats->addImpomoData(list->getPTasks().at(current)->getDuration());

    if(!list->getPTasks().at(current)->getStatus())
        notifications->playSound();
    nextPhase();
}
void ExtendedPomodoro::updateTime(int time){
    remainingTime = time;
    saveSessionStateToFile();
}
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

void ExtendedPomodoro::saveSessionStateToFile() {
    QJsonObject state;
    state["current"] = current;
    state["tasksFinished"] = tasksFinished;
    state["savedTime"] = remainingTime;

    QJsonDocument stateData(state);

    QFile file("ExtendedPomodoroSessionState.json");
    if(!file.open(QIODevice::WriteOnly))
        return;

    file.write(stateData.toJson());
    file.close();
}
void ExtendedPomodoro::loadSessionStateFromFile() {
    QFile file("ExtendedPomodoroSessionState.json");
    if(!file.open(QIODevice::ReadOnly)) {
        current = 0;
        tasksFinished = 0;
        if(list->taskCount() != 0)
            remainingTime = list->getPTasks().at(0)->getDuration();
        else
            remainingTime = 25;
        return;
    }

    QByteArray stateData = file.readAll();
    file.close();

    QJsonDocument StateFile(QJsonDocument::fromJson(stateData));
    if(!StateFile.isObject())
        return;

    QJsonObject StateJson = StateFile.object();

    current = StateJson["current"].toInt(0);
    tasksFinished = StateJson["tasksFinished"].toInt(0);
    remainingTime = StateJson["savedTime"].toInt(25);
}
void ExtendedPomodoro::loadFromDatabase() {
    list->loadFromDatabase();
    if(list->taskCount() == 0) {
        clearAllTasks();
    } else {
        if(list->getPTasks().last()->getStatus()) {//same szare zadania
            current = (list->taskCount() - 1);
            timer->setTime(0);
            currTaskLabel->setText("All tasks finished");
        } else {
            timer->setTime(list->getPTasks().at(current)->getDuration()*60);
            timer->setRemainingTime(remainingTime);//!!!!!!!!!!!!!
            updateCurrentTaskLabel();
        }
    }
}
