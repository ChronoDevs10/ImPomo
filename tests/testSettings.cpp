#include <QTest>
#include "../appsettings.h"

class TestAppSettings : public QObject {
    Q_OBJECT

private slots:

    void testEnableDisableReminders();
    void testSetTheme();
    void testSaveAndLoadSettingsFromFile();
};

void TestAppSettings::testEnableDisableReminders() {
    AppSettings settings;
    //settings.enableReminders();
    QVERIFY(settings.getSoundStatus());

    //settings.disableReminders();
    QVERIFY(!settings.getSoundStatus());
}

void TestAppSettings::testSetTheme() {
    AppSettings settings;
    settings.setTheme("dark");
    //QCOMPARE(settings.getTheme(), "dark");

    settings.setTheme("light");
    //QCOMPARE(settings.getTheme(), "light");
}

void TestAppSettings::testSaveAndLoadSettingsFromFile() {
    AppSettings settings;
    //settings.enableReminders();
    settings.setTheme("dark");

    settings.saveSettingsToFile();

    AppSettings settings2;
    settings2.loadSettingsFromFile();

    QVERIFY(settings2.getSoundStatus());
    //QCOMPARE(settings2.getTheme(), "dark");
}

//QTEST_MAIN(TestAppSettings)
#include "testSettings.moc"
