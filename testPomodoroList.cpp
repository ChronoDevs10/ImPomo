#include <QTest>
#include "pomodorolist.h"
#include "pomodorotask.h"

class TestPomodoroList : public QObject {
    Q_OBJECT

private slots:
    void testAddTask();
    void testRemoveTask();
    void testEditTaskName();
    void testEditTaskStatus();
    void testEditTaskDuration();
    void testReorderTasks();
};

void TestPomodoroList::testAddTask() {
    PomodoroList list;
    PomodoroTask task("Test Task", 25);

    list.addTask(&task);
    QCOMPARE(list.taskCount(), 1);
}

void TestPomodoroList::testEditTaskDuration() {
    PomodoroList list;
    PomodoroTask task("Test Task", 25);
    list.addTask(&task);

    list.editTaskDuration(&task, 30);
    QCOMPARE(task.getDuration(), 30);
}

void TestPomodoroList::testRemoveTask() {
    PomodoroList list;
    PomodoroTask task("Test Task", 25);

    list.addTask(&task);
    list.removeTask(&task);
    QCOMPARE(list.taskCount(), 0);
}

void TestPomodoroList::testEditTaskName() {
    PomodoroList list;
    PomodoroTask task("Test Task", 25);
    list.addTask(&task);

    list.editTaskName(&task, "New Name");
    QCOMPARE(task.getName(), QString("New Name"));
}

void TestPomodoroList::testEditTaskStatus() {
    PomodoroList list;
    PomodoroTask task("Test Task", 25);
    list.addTask(&task);

    list.editTaskStatus(&task);
    QVERIFY(task.getStatus() == false);
}

void TestPomodoroList::testReorderTasks() {
    PomodoroList list;
    PomodoroTask task1("Test Task", 25);
    PomodoroTask task2("Test Task2", 25);

    list.addTask(&task1);
    list.addTask(&task2);

    QVector<Task*> newOrder = {&task2, &task1};
    list.reorderTasks(newOrder);
    QVector<PomodoroTask*> currentOrder = list.getPTasks();

    QCOMPARE(currentOrder.size(), newOrder.size());
    for (int i = 0; i < newOrder.size(); i++)
        QCOMPARE(currentOrder[i], newOrder[i]);
}
//QTEST_MAIN(TestPomodoroList)
#include "testPomodoroList.moc"
