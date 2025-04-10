#ifndef ITIMER_H
#define ITIMER_H

#include "itimerobserver.h"

class ITimer {
public:
    virtual void setTime(int duration) = 0;
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void reset() = 0;
    virtual void subscribe(ITimerObserver* observer) = 0;
    virtual void unsubscribe(ITimerObserver* observer) = 0;
};

#endif // ITIMER_H
