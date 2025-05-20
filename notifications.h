#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QString>
#include "appsettings.h"

class Notifications {
public:
    AppSettings* settings;
    void playSound();
    void sendNotification(QString message);
};

#endif // NOTIFICATIONS_H
