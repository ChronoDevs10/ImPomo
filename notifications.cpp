#include "notifications.h"
#include <QSoundEffect>
#include <QUrl>

void Notifications::playSound() {
    static QSoundEffect sound_tada;
    static QSoundEffect softAlarm;
    sound_tada.setSource(QUrl("qrc:/tada.wav"));
    sound_tada.setVolume(0.9);
    softAlarm.setSource(QUrl("qrc:/Alarm02.wav"));
    softAlarm.setVolume(0.9);

    if(settings->getSoundStatus()) {
        if(settings->getSoundType() == "Soft Alarm")
            softAlarm.play();
        else if(settings->getSoundType() == "Fanfares")
            sound_tada.play();
    }
}
