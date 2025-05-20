#include "notifications.h"
#include <QSoundEffect>
#include <QUrl>

void Notifications::playSound() {
    static QSoundEffect sound_tada;
    sound_tada.setSource(QUrl::fromLocalFile("tada.wav"));
    sound_tada.setVolume(0.9);

    if(settings->getSoundStatus())
        sound_tada.play();
}

void Notifications::sendNotification(QString message) {}
