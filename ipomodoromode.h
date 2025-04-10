#ifndef IPOMODOROMODE_H
#define IPOMODOROMODE_H

class IPomodoroMode {
public:
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void reset() = 0;
    virtual void nextPhase() = 0;
    virtual void saveSessionStateToFile() = 0;
    virtual void loadSessionStateFromFile() = 0;
};

#endif // IPOMODOROMODE_H
