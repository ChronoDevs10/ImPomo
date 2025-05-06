#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStackedWidget>
#include <QCheckBox>


#include "todolist.h"
#include "pomodorolist.h"
#include "classicpomodoro.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addTaskField();

    void showHomeTab();
    void showToDoList();
    void showImPomodoro();
    void showPomodoro();
    void showStatistics();
    void showSettings();

private:
    QWidget *central;
    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QPushButton *addButton;
    QStackedWidget *stackedWidget;

    ToDoList *toDoList;
    PomodoroList* pomodoroList;
    ClassicPomodoro* classicPomodoro;

    QScrollArea* imPomodoroScrollArea;
    QVBoxLayout* imPomodoroScrollLayout;

    void setupHomeTab();
    void setupToDoListTab();
    void setupImPomodoroTab();
    void setupPomodoroTab();
    void setupStatisticsTab();
    void setupSettingsTab();
    QPushButton* createMenuButton();

    //void refreshPomodoroTab();
};

#endif // MAINWINDOW_H
