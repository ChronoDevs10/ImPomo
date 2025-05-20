#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>

class AppSettings {
private:
    bool soundStatus;
    QString theme;
    QString sound;
public:
    AppSettings();
    bool getSoundStatus();
    QString getTheme();
    QString getSoundType();

    void setSoundStatus(bool isEnabled);
    void setTheme(QString theme);
    void setSound(QString sound);

    void saveSettingsToFile();
    void loadSettingsFromFile();
};

#endif // APPSETTINGS_H
