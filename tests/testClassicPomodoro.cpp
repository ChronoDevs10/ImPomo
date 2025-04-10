#include <QTest>
#include "../classicpomodoro.h"

class TestClassicPomodoro : public QObject {
    Q_OBJECT

private slots:
    void testDefaultValues();
    void testChangeProperties();
    void testPhaseTransition();
    void testStart();
    void testStop();
    void testSaveAndLoadSettingsToFile();
};

void TestClassicPomodoro::testDefaultValues() {
    ClassicPomodoro pomodoro;
    QCOMPARE(pomodoro.getWorkDuration(), 25);
    QCOMPARE(pomodoro.getShortBreakDuration(), 5);
    QCOMPARE(pomodoro.getLongBreakDuration(), 15);
}

void TestClassicPomodoro::testChangeProperties() {
    ClassicPomodoro pomodoro;
    pomodoro.changeProperties(30, 10, 20, 4);
    QCOMPARE(pomodoro.getWorkDuration(), 30);
    QCOMPARE(pomodoro.getShortBreakDuration(), 10);
}

void TestClassicPomodoro::testPhaseTransition() {
    ClassicPomodoro pomodoro;
    pomodoro.start();
    pomodoro.nextPhase();
    QVERIFY(pomodoro.getcurrentPhase() != "Work");
}

void TestClassicPomodoro::testStart() {
    ClassicPomodoro pomodoro;
    pomodoro.changeProperties(2, 1, 5, 4);
    pomodoro.start();
    QTest::qWait(1500);
    QVERIFY(pomodoro.timer.getRemainingTime() < 2 * 60);
}

void TestClassicPomodoro::testStop() {
    ClassicPomodoro pomodoro;
    pomodoro.changeProperties(2, 1, 5, 4);
    pomodoro.start();
    QTest::qWait(1000);
    pomodoro.pause();
    int remaining = pomodoro.timer.getRemainingTime();
    QTest::qWait(1000);
    QCOMPARE(pomodoro.timer.getRemainingTime(), remaining);
}

void TestClassicPomodoro::testSaveAndLoadSettingsToFile() {
    ClassicPomodoro pomodoro;
    pomodoro.changeProperties(10,1,2,3);

    pomodoro.saveSessionStateToFile();

    ClassicPomodoro pomodoro2;
    pomodoro2.loadSettingsFromFile();

    QCOMPARE(pomodoro.getWorkDuration(), 25);
    QCOMPARE(pomodoro.getShortBreakDuration(), 5);
    QCOMPARE(pomodoro.getLongBreakDuration(), 15);
    QCOMPARE(pomodoro.getCycles(), 4);
}

//QTEST_MAIN(TestClassicPomodoro)
#include "testClassicPomodoro.moc"
