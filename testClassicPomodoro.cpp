#include <QTest>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "classicpomodoro.h"

class TestClassicPomodoro : public QObject
{
    Q_OBJECT

private slots:
    void testDefaultValues();
    void testChangeProperties();
    void testPhaseTransition();
    void testStart();
    void testStop();
    void testSaveSessionStateToFile();
    void testLoadSessionStateFromFile();
};

void TestClassicPomodoro::testDefaultValues()
{
    ClassicPomodoro pomodoro;
    QCOMPARE(pomodoro.getWorkDuration(), 25);
    QCOMPARE(pomodoro.getShortBreakDuration(), 5);
    QCOMPARE(pomodoro.getLongBreakDuration(), 15);
}

void TestClassicPomodoro::testChangeProperties()
{
    ClassicPomodoro pomodoro;
    pomodoro.changeProperties(30, 10, 20, 4);
    QCOMPARE(pomodoro.getWorkDuration(), 30);
    QCOMPARE(pomodoro.getShortBreakDuration(), 10);
}

void TestClassicPomodoro::testPhaseTransition()
{
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

void TestClassicPomodoro::testSaveSessionStateToFile()
{
    ClassicPomodoro pomodoro;
    pomodoro.changeProperties(10,1,2,3);

    QString filePath = "pomodoro_state.json";

    pomodoro.saveSessionStateToFile();

    QFile file(filePath);
    QVERIFY(file.exists());

    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = doc.object();

    QCOMPARE(jsonObj["workDuration"].toInt(), 25);
    QCOMPARE(jsonObj["shortBreakDuration"].toInt(), 5);
    QCOMPARE(jsonObj["longBreakDuration"].toInt(), 15);
    QCOMPARE(jsonObj["cycles"].toInt(), 4);
    QCOMPARE(jsonObj["workBlocksInCycle"].toInt(), 4);
}

void TestClassicPomodoro::testLoadSessionStateFromFile()
{
    QString filePath = "pomodoro_state.json";

    ClassicPomodoro pomodoro;

    pomodoro.loadSessionStateFromFile();

    QCOMPARE(pomodoro.getWorkDuration(), 25);
    QCOMPARE(pomodoro.getShortBreakDuration(), 5);
    QCOMPARE(pomodoro.getLongBreakDuration(), 15);
    QCOMPARE(pomodoro.getCycles(), 4);
}


QTEST_MAIN(TestClassicPomodoro)
#include "testClassicPomodoro.moc"
