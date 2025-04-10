#include <QTest>
#include "Notifications.h"

class TestNotifications : public QObject {
    Q_OBJECT

private slots:
    void testSendNotification();
    void testPlaySound();
};

void TestNotifications::testSendNotification() {
    Notifications notif;
    bool result = notif.sendNotification("Test message");
    QVERIFY(result); // Sprawdzenie, czy powiadomienie zostało wysłane
}

void TestNotifications::testPlaySound() {
    Notifications notif;
    bool result = notif.playSound();
    QVERIFY(result); // Sprawdzenie, czy dźwięk został odtworzony
}

//QTEST_MAIN(TestNotifications)
#include "testNotifications.moc"
