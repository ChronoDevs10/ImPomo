#include <QtTest>
#include "task.h"  

class TestTask : public QObject {
    Q_OBJECT

private slots:
    void testEditName();   
    void testEditStatus(); 
};

void TestTask::testEditName() {
    Task task("Old Task");
    QCOMPARE(task.getName(), QString("Old Task"));
    task.editName("New Task");
    QCOMPARE(task.getName(), QString("New Task"));
}


void TestTask::testEditStatus() {
    Task task("Task with Status");
    QCOMPARE(task.getStatus(), false);
    task.editStatus();
    QCOMPARE(task.getStatus(), true);
    task.editStatus();
    QCOMPARE(task.getStatus(), false);
}

QTEST_MAIN(TestTask)
#include "test_task.moc"
