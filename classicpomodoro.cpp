#include "classicpomodoro.h"

#include "classicpomodoro.h"
#include <QLabel>
#include <QTimer>

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
    if(currentCycle < cycles) {
        if((currentPhase == "Work") && (currentWorkBlock < workBlocksInCycle - 1)) {
            currentWorkBlock++;
            phaseLabel->setText("Current phase: Short break");
            currentPhase = "Short break";
            timer->setTime(shortBreakDuration);
            timer->start();
        }
        else if((currentPhase == "Work") && (currentWorkBlock == workBlocksInCycle - 1)) {
            phaseLabel->setText("Current phase: Long break");
            currentPhase = "Long break";
            timer->setTime(longBreakDuration);
            timer->start();
            currentCycle++;
            currentWorkBlock = 0;
        }
        else if(currentPhase == "Short break") {
            phaseLabel->setText("Current phase: Work");
            currentPhase = "Work";
            timer->setTime(workDuration);
            timer->start();
        }
        else if(currentPhase == "Long break") {
            phaseLabel->setText("Current phase: Work");
            currentPhase = "Work";
            timer->setTime(workDuration);
            timer->start();
        }
    }
    else {
        phaseLabel->setText("Session finished");
        timer->setTime(workDuration);
        currentPhase = "Work";
        currentWorkBlock = 0;
        currentCycle = 0;

        QTimer::singleShot(3000, [this]() {
            phaseLabel->setText("Current phase: Work");
        });
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
void ClassicPomodoro::changeProperties(int newWork, int newShortBreak, int newLongBreak, int newCycles, int workBlocks) {
    workDuration = newWork;
    shortBreakDuration = newShortBreak;
    longBreakDuration = newLongBreak;
    cycles = newCycles;
    workBlocksInCycle = workBlocks;

    if(!(timer->isRunning)){
        if(currentPhase == "Work")
            timer->setTime(newWork);
        else if(currentPhase == "Short break")
            timer->setTime(newShortBreak);
        else if(currentPhase == "Long break")
            timer->setTime(newLongBreak);

        /*Zmiana cycles i workBlocks/blokada zmiany*/
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
