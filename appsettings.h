#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>

class AppSettings {
private:
    bool soundEnabled;
    bool visualEnabled;
    QString theme;
public:
    bool getSoundStatus();
    void enableReminders();
    void disableReminders();
    QString getTheme();
    void setTheme(bool isDarkMode);
    void saveSettingsToFile();
    void loadSettingsFromFile();
};

#endif // APPSETTINGS_H
