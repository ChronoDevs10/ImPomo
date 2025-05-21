#include "appsettings.h"

AppSettings::AppSettings() {
    soundStatus = true;
    theme = "Dark";
    sound = "Soft Alarm";
}

bool AppSettings::getSoundStatus() {
    return soundStatus;
}
QString AppSettings::getTheme() {
    return theme;
}
QString AppSettings::getSoundType() {
    return sound;
}

void AppSettings::setSoundStatus(bool isEnabled) {
    soundStatus = isEnabled;
}
void AppSettings::setTheme(QString newTheme) {
    theme = newTheme;
}
void AppSettings::setSound(QString newSound) {
    sound = newSound;
}

void AppSettings::saveSettingsToFile() {}
void AppSettings::loadSettingsFromFile() {}
