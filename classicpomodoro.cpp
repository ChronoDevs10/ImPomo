#include "classicpomodoro.h"

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
            stats->addClassicPomodoroData(workDuration);
            currentWorkBlock++;
            phaseLabel->setText("Current phase: Short break");
            currentPhase = "Short break";
            timer->setTime(shortBreakDuration);
            timer->start();
        }
        else if((currentPhase == "Work") && (currentWorkBlock == workBlocksInCycle - 1)) {
            stats->addClassicPomodoroData(workDuration);
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
    saveSessionStateToFile();
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

    if(currentPhase == "Work")
        timer->setTime(newWork);
    else if(currentPhase == "Short break")
        timer->setTime(newShortBreak);
    else if(currentPhase == "Long break")
        timer->setTime(newLongBreak);

    if(newCycles >= currentCycle + 1)
        cycles = newCycles;
    if(workBlocks >= currentWorkBlock + 1)
        workBlocksInCycle = workBlocks;
}
void ClassicPomodoro::update() {
    nextPhase();
    notifications->playSound();
}

void ClassicPomodoro::loadSettingsFromFile() {
    QFile file("ClassicPomodoroSettings.json");
    if(!file.open(QIODevice::ReadOnly))
        return;

    QByteArray SettingsData = file.readAll();
    file.close();

    QJsonDocument SettingsFile(QJsonDocument::fromJson(SettingsData));
    if(!SettingsFile.isObject())
        return;

    QJsonObject SettingsJson = SettingsFile.object();

    changeProperties(SettingsJson["workDuration"].toInt(25),
                    SettingsJson["shortBreakDuration"].toInt(5),
                    SettingsJson["longBreakDuration"].toInt(15),
                    SettingsJson["cycles"].toInt(4),
                    SettingsJson["workBlocksInCycle"].toInt(4) );
}

void ClassicPomodoro::saveSettingsToFile() {
    QJsonObject settings;
    settings["workDuration"] = workDuration;
    settings["shortBreakDuration"] = shortBreakDuration;
    settings["longBreakDuration"] = longBreakDuration;
    settings["cycles"] = cycles;
    settings["workBlocksInCycle"] = workBlocksInCycle;

    QJsonDocument SettingsFile(settings);

    QFile file("ClassicPomodoroSettings.json");
    if(!file.open(QIODevice::WriteOnly))
        return;

    file.write(SettingsFile.toJson());
    file.close();
}

void ClassicPomodoro::saveSessionStateToFile() {
    QJsonObject state;
    state["currentWorkBlock"] = currentWorkBlock;
    state["currentCycle"] = currentCycle;
    state["currentPhase"] = currentPhase;

    QJsonDocument stateData(state);
    QFile file("ClassicPomodoroSessionState.json");
    if(!file.open(QIODevice::WriteOnly))
        return;

    file.write(stateData.toJson());
    file.close();
}
void ClassicPomodoro::loadSessionStateFromFile() {
    QFile file("ClassicPomodoroSessionState.json");
    if(!file.open(QIODevice::ReadOnly))
        return;

    QByteArray stateData = file.readAll();
    file.close();

    QJsonDocument StateFile(QJsonDocument::fromJson(stateData));
    if(!StateFile.isObject())
        return;

    QJsonObject StateJson = StateFile.object();

    currentWorkBlock = StateFile["currentWorkBlock"].toInt(0);
    currentCycle = StateFile["currentCycle"].toInt(0);
    currentPhase = StateFile["currentPhase"].toString("Work");
}
