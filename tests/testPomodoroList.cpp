#include <QTest>
#include "../pomodorolist.h"
#include "../pomodorotask.h"

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
    QVERIFY(task.getStatus() == true);
}

void TestPomodoroList::testReorderTasks() {
    PomodoroList list;
    PomodoroTask task1("Test Task1", 20);
    PomodoroTask task2("Test Task2", 10);
    PomodoroTask task3("Test Task3", 1);

    list.addTask(&task1);
    list.addTask(&task2);
    list.addTask(&task3);

    list.reorderTasks(0, 2);

    QVector<PomodoroTask*> currentOrder = list.getPTasks();

    QCOMPARE(currentOrder.size(), 3);
    QCOMPARE(currentOrder[0], &task2);
    QCOMPARE(currentOrder[1], &task3);
    QCOMPARE(currentOrder[2], &task1);

    list.reorderTasks(1, 2);

    currentOrder = list.getPTasks();

    QCOMPARE(currentOrder[0], &task2);
    QCOMPARE(currentOrder[1], &task1);
    QCOMPARE(currentOrder[2], &task3);

    list.reorderTasks(0, 1);

    currentOrder = list.getPTasks();

    QCOMPARE(currentOrder[0], &task1);
    QCOMPARE(currentOrder[1], &task2);
    QCOMPARE(currentOrder[2], &task3);
}
//QTEST_MAIN(TestPomodoroList)
#include "testPomodoroList.moc"
