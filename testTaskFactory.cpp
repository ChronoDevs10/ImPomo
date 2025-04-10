#include <QTest>
#include "taskfactory.h"

class TestTaskFactory : public QObject
{
    Q_OBJECT

private slots:
    void testCreateRegularTask();
    void testCreatePomodoroTask();
    void testInvalidTaskType();
};

void TestTaskFactory::testCreateRegularTask()
{
    Task* task = TaskFactory::createTask("regular", "Test Task");
    QVERIFY(task != nullptr);
    QCOMPARE(task->getName(), QString("Test Task"));
    delete task;
}

void TestTaskFactory::testCreatePomodoroTask()
{
    Task* task = TaskFactory::createTask("pomodoro", "Test Task", 25);
    QVERIFY(task != nullptr);
    QCOMPARE(task->getName(), QString("Test Task"));
    delete task;
}

void TestTaskFactory::testInvalidTaskType()
{
    Task* task = TaskFactory::createTask("invalid", "Test Task");
    QVERIFY(task == nullptr);
}

//QTEST_MAIN(TestTaskFactory)
#include "testTaskFactory.moc"
