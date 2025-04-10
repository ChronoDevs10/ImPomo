#include "timer.h"

void Timer::setTime(int duration) {}
void Timer::start() {}
void Timer::pause() {}
void Timer::reset() {}
void Timer::subscribe(ITimerObserver* observer) {}
void Timer::unsubscribe(ITimerObserver* observer) {}
int Timer::getRemainingTime() {
    return 10000;
}
