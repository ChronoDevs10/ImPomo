#include <QTest>
#include "../task.h"

class TestTask : public QObject {
    Q_OBJECT

private slots:
    void testEditStatus();
    void testEditName();
    void testGetStatus();
    void testGetName();
    void testEditNameLong();
};

void TestTask::testEditStatus() {
    Task task("Test Task");
    task.editStatus();
    QVERIFY(task.getStatus() == true);

    task.editStatus();
    task.editStatus();
    QVERIFY(task.getStatus() == true);
}

void TestTask::testEditName() {
    Task task("Test Task");
    task.editName("New Task Name");
    QCOMPARE(task.getName(), QString("New Task Name"));
}

void TestTask::testGetStatus() {
    Task task("Test Task");
    QVERIFY(task.getStatus() == false);
}

void TestTask::testGetName() {
    Task task("Test Task");
    QCOMPARE(task.getName(), QString("Test Task"));
}

void TestTask::testEditNameLong() {
    Task task("Test Task");
    QString longName(1000, '!');
    task.editName(longName);
    QCOMPARE(task.getName(), longName);
}

//QTEST_MAIN(TestTask)
#include "testTask.moc"
