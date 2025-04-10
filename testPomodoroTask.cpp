#include <QtTest>
#include "pomodorotask.h"

class TestPomodoroTask : public QObject {
    Q_OBJECT

private slots:
    void testGetDuration();
    void testEditDuration();
    void testInheritance();
    void testEditDurationZero();
    void testEditDurationNegative();
    void testEditDurationLargeValue();
};

void TestPomodoroTask::testGetDuration() {
    PomodoroTask task("Test Task", 25);
    QCOMPARE(task.getDuration(), 25);
}

void TestPomodoroTask::testEditDuration() {
    PomodoroTask task("Test Task", 25);
    task.editDuration(30);
    QCOMPARE(task.getDuration(), 30);
}

void TestPomodoroTask::testInheritance() {
    PomodoroTask task("Test Task", 25);
    QCOMPARE(task.getName(), QString("Test Task"));
    QVERIFY(task.getStatus() == false);
}

void TestPomodoroTask::testEditDurationZero() {
    PomodoroTask task("Test Task", 25);
    task.editDuration(0);
    QCOMPARE(task.getDuration(), 0);
}

void TestPomodoroTask::testEditDurationNegative() {
    PomodoroTask task("Test Task", 25);
    task.editDuration(-10);
    QCOMPARE(task.getDuration(), 0);
}

void TestPomodoroTask::testEditDurationLargeValue() {
    PomodoroTask task("Test Task", 25);
    task.editDuration(1000);
    QCOMPARE(task.getDuration(), 1000);
}

QTEST_MAIN(TestPomodoroTask)
#include "testPomodoroTask.moc"
