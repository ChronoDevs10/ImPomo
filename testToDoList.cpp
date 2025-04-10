#include <QTest>
#include "todolist.h"
#include "task.h"

class TestToDoList : public QObject {
    Q_OBJECT

private slots:
    void testAddTask();
    void testRemoveTask();
    void testEditTaskName();
    void testEditTaskStatus();
    void testReorderTasks();
    void testSaveAndLoad();
    void testUpdate();
};

void TestToDoList::testAddTask() {
    ToDoList list;
    Task task("Test Task");

    list.addTask(&task);
    QCOMPARE(list.taskCount(), 1);
}

void TestToDoList::testRemoveTask() {
    ToDoList list;
    Task task("Test Task");

    list.addTask(&task);
    list.removeTask(&task);
    QCOMPARE(list.taskCount(), 0);
}

void TestToDoList::testEditTaskName() {
    ToDoList list;
    Task task("Test Task");
    list.addTask(&task);

    list.editTaskName(&task, "New Name");
    QCOMPARE(task.getName(), QString("New Name"));
}

void TestToDoList::testEditTaskStatus() {
    ToDoList list;
    Task task("Test Task");
    list.addTask(&task);

    list.editTaskStatus(&task);
    QVERIFY(task.getStatus() == true);
}

void TestToDoList::testReorderTasks() {
    ToDoList list;
    Task task1("Test Task1");
    Task task2("Test Task2");

    list.addTask(&task1);
    list.addTask(&task2);

    QVector<Task*> newOrder = {&task2, &task1};
    list.reorderTasks(newOrder);
    QVector<Task*> currentOrder = list.getTasks();

    QCOMPARE(currentOrder.size(), newOrder.size());
    for (int i = 0; i < newOrder.size(); ++i)
        QCOMPARE(currentOrder[i], newOrder[i]);
}

void TestToDoList::testSaveAndLoad() {
    Task t1("task 1");
    Task t2("task 2");

    ToDoList list;
    list.addTask(&t1);
    list.addTask(&t2);

    list.saveToDatabase();

    ToDoList loaded;
    loaded.loadFromDatabase();

    QCOMPARE(loaded.taskCount(), 2);
    QVERIFY(!loaded.getTasks().empty());
    QCOMPARE(loaded.getTasks()[0]->getName(), QString("task 1"));
}

void TestToDoList::testUpdate() {
    Task original("Task A");
    ToDoList list;
    list.addTask(&original);
    list.saveToDatabase();

    original.editName("Task B");
    list.updateInDatabase(&original);

    ToDoList loaded;
    loaded.loadFromDatabase();
    QVERIFY(!loaded.getTasks().empty());
    QCOMPARE(loaded.getTasks()[0]->getName(), QString("Task B"));
}

//QTEST_MAIN(TestToDoList)
#include "testToDoList.moc"
