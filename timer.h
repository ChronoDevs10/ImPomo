#ifndef TIMER_H
#define TIMER_H

#include "itimer.h"
#include "itimerobserver.h"
#include <QVector>

class Timer : public ITimer {

private:
    int remainingTime;
    QVector<ITimerObserver*> subscribers;
public:
    void setTime(int duration) override;
    void start() override;
    void pause() override;
    void reset() override;
    void subscribe(ITimerObserver* observer) override;
    void unsubscribe(ITimerObserver* observer) override;

    int getRemainingTime();
};

#endif // TIMER_H
