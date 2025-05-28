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

void AppSettings::saveSettingsToFile() {
    QJsonObject settings;
    settings["soundStatus"] = soundStatus;
    settings["theme"] = theme;
    settings["sound"] = sound;

    QJsonDocument SettingsFile(settings);
    QFile file("AppSettings.json");
    if(!file.open(QIODevice::WriteOnly))
        return;

    file.write(SettingsFile.toJson());
    file.close();
}
void AppSettings::loadSettingsFromFile() {
    QFile file("AppSettings.json");
    if(!file.open(QIODevice::ReadOnly)) {
        soundStatus = true;
        theme = "Dark";
        sound = "Soft Alarm";
        return;
    }

    QByteArray SettingsData = file.readAll();
    file.close();

    QJsonDocument SettingsFile(QJsonDocument::fromJson(SettingsData));
    if(!SettingsFile.isObject())
        return;

    QJsonObject SettingsJson = SettingsFile.object();

    soundStatus = SettingsJson["soundStatus"].toBool(true);
    theme = SettingsFile["theme"].toString("Dark");
    sound = SettingsJson["sound"].toString("Soft Alarm");
}
