#include "timer.h"
#include <QDebug>

Timer::Timer() : remainingTime(0), isRunning(false) {
    timeLabel = new QLabel("00:00");
    startButton = new QPushButton("Start");
    pauseButton = new QPushButton("Pause");
    resetButton = new QPushButton("Reset");
    timer = new QTimer();
    remainingTime = 0;
    startTime = 0;

    QObject::connect(startButton, &QPushButton::clicked, this, &Timer::start);
    QObject::connect(pauseButton, &QPushButton::clicked, this, &Timer::pause);
    QObject::connect(resetButton, &QPushButton::clicked, this, &Timer::reset);

    QObject::connect(timer, &QTimer::timeout, this, &Timer::updateTime);
}

Timer::~Timer() {
    delete timeLabel;
    delete startButton;
    delete pauseButton;
    delete resetButton;
    delete timer;
}

void Timer::setTime(int duration) {
    startTime = duration;
    remainingTime = duration;
    updateLabel();
}

void Timer::start() {
    emit started();
    if(!isRunning) {
        timer->start(1000);
        isRunning = true;
    }
}

void Timer::pause() {
    if(isRunning) {
        timer->stop();
        isRunning = false;
    }
}

void Timer::reset() {
    timer->stop();
    isRunning = false;
    remainingTime = startTime;
    updateLabel();
}

int Timer::getRemainingTime() {
    return remainingTime;
}
int Timer::getStartTime(){
    return startTime;
}

void Timer::updateTime() {
    if(remainingTime > 0) {
        --remainingTime;
        updateLabel();
    } else {
        timer->stop();
        isRunning = false;
        subscriber->update();
    }
}

void Timer::setSubscriber(ITimerObserver* observer){
    subscriber = observer;
}

ITimerObserver* Timer::getSubscriber() {
    return subscriber;
}

void Timer::updateLabel() {
    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;
    timeLabel->setText(QString::asprintf("%02d:%02d", minutes, seconds));
}

