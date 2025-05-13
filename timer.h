#ifndef TIMER_H
#define TIMER_H

#include "itimer.h"
#include "itimerobserver.h"
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

class Timer : public QObject, public ITimer{
    Q_OBJECT
private:
    int startTime;
    int remainingTime;
    ITimerObserver* subscriber;
public:
    QTimer* timer;
    bool isRunning;

    Timer();
    ~Timer();

    void setTime(int duration) override;
    void start() override;
    void pause() override;
    void reset() override;

    int getRemainingTime();
    int getStartTime();
    void setRemainingTime(int newTime);
    void setStartTime(int newTime);

    void updateTime();
    void updateLabel();

    void setSubscriber(ITimerObserver* observer);
    ITimerObserver* getSubscriber();

    QLabel* timeLabel;
    QPushButton* startButton;
    QPushButton* pauseButton;
    QPushButton* resetButton;
};

#endif // TIMER_H
