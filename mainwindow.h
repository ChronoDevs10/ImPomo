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
#include "extendedpomodoro.h"
#include "statistics.h"
#include "appsettings.h"
#include "notifications.h"

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
    void PomodoroSettings();

private:
    QWidget *central;
    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QPushButton *addButton;
    QStackedWidget *stackedWidget;

    ToDoList *toDoList;
    PomodoroList* pomodoroList;
    ClassicPomodoro* classicPomodoro;
    ExtendedPomodoro* extendedPomodoro;
    AppSettings* appSettings;
    Statistics* statistics;
    Notifications* notifications;

    QScrollArea* imPomodoroScrollArea;
    QVBoxLayout* imPomodoroScrollLayout;

    int taskIdx;

    void setupHomeTab();
    void setupToDoListTab();
    void setupImPomodoroTab();
    void setupPomodoroTab();
    void setupStatisticsTab();
    void setupSettingsTab();
    QPushButton* createMenuButton();
    void setStyle(int style);
    void setStyleHome(int style);
    void setStyleToDo(int style);
    void setStyleImPomo(int style);
    void setStyleClassPomo(int style);
    void setStyleStats(int style);
    void setStyleSett(int style);
    QString getTimerStyle(int style);
    QString getTimerButtonStyle(int style);
};

#endif // MAINWINDOW_H
