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
    settings.setSoundStatus(true);
    QVERIFY(settings.getSoundStatus());

    settings.setSoundStatus(false);
    QVERIFY(!settings.getSoundStatus());
}

void TestAppSettings::testSetTheme() {
    AppSettings settings;
    settings.setTheme("dark");
    QCOMPARE(settings.getTheme(), "dark");

    settings.setTheme("light");
    QCOMPARE(settings.getTheme(), "light");
}

void TestAppSettings::testSaveAndLoadSettingsFromFile() {
    AppSettings settings;
    settings.setSoundStatus(true);
    settings.setTheme("dark");
    settings.saveSettingsToFile();

    settings.setSoundStatus(false);
    settings.setTheme("light");

    settings.loadSettingsFromFile();
    QVERIFY(settings.getSoundStatus());
    QCOMPARE(settings.getTheme(), "dark");
}

//QTEST_MAIN(TestAppSettings)
#include "testSettings.moc"
