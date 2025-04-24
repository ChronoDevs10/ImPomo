#include <QTest>
#include "../taskfactory.h"

class TestTaskFactory : public QObject {
    Q_OBJECT

private slots:
    void testCreateRegularTask();
    void testCreatePomodoroTask();
    void testInvalidTaskType();
};

void TestTaskFactory::testCreateRegularTask() {
    Task* task = TaskFactory::createTask("Basic", "Test Task");
    QVERIFY(task != nullptr);
    QCOMPARE(task->getName(), QString("Test Task"));
    delete task;
}

void TestTaskFactory::testCreatePomodoroTask() {
    Task* task = TaskFactory::createTask("Pomodoro", "Test", 25);
    PomodoroTask* PTask = dynamic_cast<PomodoroTask*>(task);

    QVERIFY(task != nullptr);
    QCOMPARE(PTask->getName(), QString("Test"));
    QCOMPARE(PTask->getDuration(), 25);
    delete task;
}

void TestTaskFactory::testInvalidTaskType() {
    Task* task = TaskFactory::createTask("invalid", "Test Task");
    QVERIFY(task == nullptr);
}

//QTEST_MAIN(TestTaskFactory)
#include "testTaskFactory.moc"
