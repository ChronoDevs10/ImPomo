#include <QTest>
#include "../timer.h"

class Observer : public QObject, public ITimerObserver {
    Q_OBJECT

public:
    bool updated = false;
    void update() override {
        updated = true;
    }
};

class TimerTest : public QObject {
    Q_OBJECT

private slots:
    void testInitialTime();
    void testSetTime();
    void testStartTime();
    void testPauseTime();
    void testUpdate();
};

void TimerTest::testInitialTime() {
    Timer timer;
    QCOMPARE(timer.getRemainingTime(), 0);
}

void TimerTest::testSetTime() {
    Timer timer;
    timer.setTime(25 * 60);
    QCOMPARE(timer.getRemainingTime(), 25 * 60);
}

void TimerTest::testStartTime() {
    Timer timer;
    timer.setTime(3);
    timer.start();
    QTest::qWait(1100);
    QVERIFY(timer.getRemainingTime() < 3);
}

void TimerTest::testPauseTime() {
    Timer timer;
    timer.setTime(60 * 5);
    timer.start();
    QTest::qWait(1000);
    timer.pause();
    int pausedTime = timer.getRemainingTime();
    QTest::qWait(1000);

    QVERIFY(pausedTime < 3000);
    QTest::qWait(1000);
    QCOMPARE(timer.getRemainingTime(), pausedTime);
}

void TimerTest::testUpdate() {
    Timer timer;
    Observer observer;
    timer.setSubscriber(&observer);

    timer.getSubscriber()->update();

    QVERIFY(observer.updated);
}

//QTEST_MAIN(TimerTest)
#include "testTimer.moc"

