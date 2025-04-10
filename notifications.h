#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QString>

class Notifications {
public:
    bool playSound();
    bool sendNotification(QString message);
};

#endif // NOTIFICATIONS_H
