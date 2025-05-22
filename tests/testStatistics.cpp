#include <QTest>
#include "../statistics.h"
#include "../task.h"

class TestStatistics : public QObject {
    Q_OBJECT

private slots:
    void testAddCompletedTaskForDay();
    void testAddClassicPomodoroTime();
    void testGetDailyTimeWorked();
    void testGetCompletedTasksForDay();
    void testSaveAndLoadFromFile();
};

void TestStatistics::testAddCompletedTaskForDay() {
    /*
    Task task("Test task");
    Statistics statistics;
    statistics.addCompletedTaskForDay(&task, 30, "2025-04-10");

    QVector<Task*> tasks = statistics.getCompletedTasksForDay("2025-04-10");
    QCOMPARE(tasks.size(), 1);
    QCOMPARE(tasks[0]->getName(), "Test Task");
*/
}

void TestStatistics::testAddClassicPomodoroTime() {
    /*
    Statistics statistics;
    statistics.addClassicPomodoroTime("2025-04-10", 25);
    int timeWorked = statistics.getDailyTimeWorked("2025-04-10");
    QCOMPARE(timeWorked, 25);
*/
}

void TestStatistics::testGetDailyTimeWorked() {
    /*
    Statistics statistics;
    statistics.addClassicPomodoroTime("2025-04-10", 50);
    int timeWorked = statistics.getDailyTimeWorked("2025-04-10");
    QCOMPARE(timeWorked, 50);
*/
}

void TestStatistics::testGetCompletedTasksForDay() {
    /*
    Task task1("Task 1");
    Task task2("Task 2");

    Statistics statistics;
    statistics.addCompletedTaskForDay(&task1, 30, "2025-04-10");
    statistics.addCompletedTaskForDay(&task2, 45, "2025-04-10");

    QVector<Task*> tasks = statistics.getCompletedTasksForDay("2025-04-10");
    QCOMPARE(tasks.size(), 2);
    QCOMPARE(tasks[0]->getName(), "Task 1");
    QCOMPARE(tasks[1]->getName(), "Task 2");
*/
}

void TestStatistics::testSaveAndLoadFromFile() {
    /*
    Task task("Task to save");
    Statistics statistics;
    statistics.addCompletedTaskForDay(&task, 40, "2025-04-10");

    statistics.saveToFile();

    Statistics statistics2;
    statistics2.loadFromFile();

    QVector<Task*> tasks = statistics2.getCompletedTasksForDay("2025-04-10");
    QCOMPARE(tasks.size(), 1);
    QCOMPARE(tasks[0]->getName(), "Task to save");
*/
}

//QTEST_MAIN(TestStatistics)
#include "testStatistics.moc"
