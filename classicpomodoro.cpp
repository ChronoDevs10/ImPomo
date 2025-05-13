#include "classicpomodoro.h"

#include "classicpomodoro.h"
#include <QLabel>

ClassicPomodoro::ClassicPomodoro() {
    workDuration = 10;
    shortBreakDuration = 3;
    longBreakDuration = 5;
    cycles = 4;
    workBlocksInCycle = 4;

    currentWorkBlock = 0;
    currentCycle = 0;
    currentPhase = "Work";

    timer = new Timer();
    timer->setSubscriber(this);
    timer->setTime(workDuration);

    phaseLabel = new QLabel("Current phase: " + currentPhase);
    phaseLabel->setStyleSheet("font-size: 25px; font-weight: bold; margin: 10px;");
}

void ClassicPomodoro::start() {
    timer->start();
}
void ClassicPomodoro::pause() {
    timer->pause();
}
void ClassicPomodoro::reset() {
    timer->reset();
}
void ClassicPomodoro::nextPhase() {
    //więcej informacji na label?
    if((currentPhase == "Work")) {
        phaseLabel->setText("Current phase: Short break");
        currentPhase = "Short break";
        timer->setTime(shortBreakDuration);
        timer->start();
    }
    else if((currentPhase == "Short break") ){
        phaseLabel->setText("Current phase: Long break");
        currentPhase = "Long break";
        timer->setTime(longBreakDuration);
        timer->start();
    }
    else if((currentPhase == "Long break")){
        phaseLabel->setText("Current phase: Work");
        currentPhase = "Work";
        //currentWorkBlock++;
        timer->setTime(workDuration);
        timer->start();
    }
}
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
int ClassicPomodoro::getWorkBlocks() {
    return workBlocksInCycle;
}
QString ClassicPomodoro::getcurrentPhase() {
    return currentPhase;
}
void ClassicPomodoro::setCurrentPhase(QString newPhase) {
    currentPhase = newPhase;
}
void ClassicPomodoro::changeProperties(int newWork, int newShortBreak, int newLongBreak, int newCycles) {
    workDuration = newWork;
    shortBreakDuration = newShortBreak;
    longBreakDuration = newLongBreak;
    cycles = newCycles;

    if(!(timer->isRunning)){
        if(currentPhase == "Work") {
            timer->setStartTime(newWork);
            timer->setRemainingTime(newWork);
        }
        else if(currentPhase == "Short break") {
            timer->setStartTime(newShortBreak);
            timer->setRemainingTime(newShortBreak);
        }
        else if(currentPhase == "Long break") {
            timer->setStartTime(newLongBreak);
            timer->setRemainingTime(newLongBreak);
        }
    }
    timer->updateLabel();
}
void ClassicPomodoro::update() {
    nextPhase();
    //powiadomienia
}

void ClassicPomodoro::loadSettingsFromFile() {}
void ClassicPomodoro::saveSettingsToFile() {}
void ClassicPomodoro::saveSessionStateToFile() {}
void ClassicPomodoro::loadSessionStateFromFile() {}
