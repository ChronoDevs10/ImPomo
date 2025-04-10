#include "appsettings.h"

bool AppSettings::getSoundStatus() {
    return true;
}
void AppSettings::enableReminders() {}
void AppSettings::disableReminders() {}
QString AppSettings::getTheme() {
    return "";
}
void AppSettings::setTheme(bool isDarkMode) {}
void AppSettings::saveSettingsToFile() {}
void AppSettings::loadSettingsFromFile() {}
