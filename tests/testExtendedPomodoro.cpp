#include <QTest>
#include "../extendedpomodoro.h"
#include "../pomodorotask.h"

class TestExtendedPomodoro : public QObject {
    Q_OBJECT

private slots:
    void testTaskOrder();
    void testCurrentTask();
    void testAutoTransition();
};

void TestExtendedPomodoro::testTaskOrder() {
    ExtendedPomodoro pomodoro;
    PomodoroTask task1("Task 1", 25);
    PomodoroTask task2("Task 2", 30);
    PomodoroList list;

    list.addTask(&task1);
    list.addTask(&task2);

    pomodoro.list = &list;

    QVector<PomodoroTask*> newOrder = {&task2, &task1};
    //pomodoro.reorderTasks(newOrder);
    QVector<PomodoroTask*> currentOrder = list.getPTasks();

    QCOMPARE(currentOrder.size(), newOrder.size());
    for (int i = 0; i < newOrder.size(); i++)
        QCOMPARE(currentOrder[i], newOrder[i]);
}

void TestExtendedPomodoro::testCurrentTask() {
    ExtendedPomodoro pomodoro;
    PomodoroTask task("Task 1", 25);
    PomodoroList list;

    list.addTask(&task);

    pomodoro.list = &list;
    pomodoro.start();
    QCOMPARE(pomodoro.getcurrent()->getName(), "Task 1");
}

void TestExtendedPomodoro::testAutoTransition() {
    PomodoroList list;
    PomodoroTask task1("Task 1", 1);
    PomodoroTask task2("Task 2", 1);
    list.addTask(&task1); // 1 minuta
    list.addTask(&task2);

    ExtendedPomodoro pomodoro;
    pomodoro.list = &list;
    pomodoro.start();

    QTest::qWait(61000);

    QCOMPARE(pomodoro.getcurrent()->getName(), "Task 2");
}

//QTEST_MAIN(TestExtendedPomodoro)
#include "testExtendedPomodoro.moc"
