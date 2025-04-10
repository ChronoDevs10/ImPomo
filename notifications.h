#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QString>

class Notifications {
public:
    void playSound();
    void sendNotification(QString message);
};

#endif // NOTIFICATIONS_H
