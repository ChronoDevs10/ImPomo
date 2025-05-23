#include <QTest>
#include <QDebug>
#include <QTimer>
#include "../extendedpomodoro.h"
#include "../pomodorotask.h"
#include "taskfactory.h"

class TestExtendedPomodoro : public QObject {
    Q_OBJECT

private slots:

    void testTaskOrder();
    void testCurrentTask();
};

void TestExtendedPomodoro::testTaskOrder() {
    ExtendedPomodoro pomodoro;
    PomodoroList list;
    list.parent = nullptr;

    Task* baseTask1 = TaskFactory::createTask("Pomodoro", "Task 1", 5);
    PomodoroTask* task1 = dynamic_cast<PomodoroTask*>(baseTask1);

    Task* baseTask2 = TaskFactory::createTask("Pomodoro", "Task 2", 5);
    PomodoroTask* task2 = dynamic_cast<PomodoroTask*>(baseTask2);

    list.addTask(task1);
    list.addTask(task2);

    pomodoro.list = &list;

    QVector<PomodoroTask*> newOrder = {task2, task1};
    pomodoro.list->reorderTasks(0,1);
    QVector<PomodoroTask*> afterReorder = pomodoro.list->getPTasks();

    QCOMPARE(newOrder.size(), afterReorder.size());

    for(int i = 0; i < newOrder.size(); i++) {
        QCOMPARE(newOrder[i]->getName(), afterReorder[i]->getName());
        QCOMPARE(newOrder[i]->getDuration(), afterReorder[i]->getDuration());
    }
}

void TestExtendedPomodoro::testCurrentTask() {
    ExtendedPomodoro pomodoro;
    PomodoroList list;
    list.parent = nullptr;

    Task* baseTask1 = TaskFactory::createTask("Pomodoro", "Task 1", 5);
    PomodoroTask* task1 = dynamic_cast<PomodoroTask*>(baseTask1);

    list.addTask(task1);
    pomodoro.list = &list;
    pomodoro.start();
    QCOMPARE(pomodoro.list->getPTasks().at(pomodoro.getcurrent())->getName(), "Task 1");
}

//QTEST_MAIN(TestExtendedPomodoro)
#include "testExtendedPomodoro.moc"
