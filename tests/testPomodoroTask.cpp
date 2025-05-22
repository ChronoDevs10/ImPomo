#include <QTest>
#include "../pomodorotask.h"

class TestPomodoroTask : public QObject {
    Q_OBJECT

private slots:
    void testGetDuration();
    void testEditDuration();
    void testEditDurationNegative();
    void testEditDurationLargeValue();
    void testEditStatus();
    void testEditName();
    void testGetStatus();
    void testGetName();
    void testEditNameLongString();
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

void TestPomodoroTask::testEditStatus() {
    PomodoroTask task("Test Task", 25);
    task.setStatus(true);
    QVERIFY(task.getStatus() == true);

    task.setStatus(false);
    task.setStatus(true);
    QVERIFY(task.getStatus() == true);
}

void TestPomodoroTask::testEditName() {
    PomodoroTask task("Test Task", 25);
    task.editName("New Task Name");
    QCOMPARE(task.getName(), QString("New Task Name"));
}

void TestPomodoroTask::testGetStatus() {
    PomodoroTask task("Test Task", 25);
    QVERIFY(task.getStatus() == false);
}

void TestPomodoroTask::testGetName() {
    PomodoroTask task("Test Task", 25);
    QCOMPARE(task.getName(), QString("Test Task"));
}

void TestPomodoroTask::testEditNameLongString() {
    PomodoroTask task("Test Task", 25);
    QString longName(1000, '!');
    task.editName(longName);
    QCOMPARE(task.getName(), longName);
}
//QTEST_MAIN(TestPomodoroTask)
#include "testPomodoroTask.moc"
