/*
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
*/

#include "mainwindow.h"
#include "task.h"
#include "todolist.h"
#include "taskfactory.h"
#include "timer.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QMenu>
#include <QAction>
#include <QScrollArea>
#include <QTimer>
#include <QScrollBar>
#include <QDebug>
#include <QLabel>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), toDoList(new ToDoList()), pomodoroList(new PomodoroList())
{
    central = new QWidget(this);
    mainLayout = new QVBoxLayout(central);
    setCentralWidget(central);

    stackedWidget = new QStackedWidget(this);
    mainLayout->addWidget(createMenuButton(), 0, Qt::AlignTop | Qt::AlignRight);
    mainLayout->addWidget(stackedWidget);

    setupHomeTab();
    setupToDoListTab();
    setupImPomodoroTab();
    setupPomodoroTab();
    setupStatisticsTab();
    setupSettingsTab();

    addButton = new QPushButton("+", this);
    addButton->hide();

    addButton->setFixedSize(60, 60);
    addButton->setStyleSheet("QPushButton { border-radius: 30px; background-color: red; color: white; font: bold 24px; }");
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addTaskField);
    mainLayout->addWidget(addButton, 0, Qt::AlignHCenter);

    setWindowTitle("✨ImPomo✨");
    resize(600, 800);
}

MainWindow::~MainWindow() {
    delete toDoList;
    delete pomodoroList;
    delete classicPomodoro;
}

void MainWindow::setupHomeTab() {
    QWidget *startTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(startTab);

    QLabel *welcomeLabel = new QLabel("Welcome to ✨ImPomo✨");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 40px; font-weight: bold;");

    QLabel *hintLabel = new QLabel("Select a tab from the menu to get started");

    hintLabel->setAlignment(Qt::AlignCenter);
    /* Zegar
    QLabel *timeLabel = new QLabel(this);
    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setStyleSheet(
        "font-size: 30px; "
        "font-weight: bold; "
        "color: #000000; "
        "background-color: #fce4ec; "
        "border: 2px solid #000000; "
        "border-radius: 10px; "
        "padding: 10px; "
        );

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [timeLabel]() {
        QTime currentTime = QTime::currentTime();
        QString timeString = currentTime.toString("hh:mm:ss AP");
        timeLabel->setText(timeString);
    });
    timer->start(1000);

    QTime currentTime = QTime::currentTime();
    timeLabel->setText(currentTime.toString("hh:mm:ss AP"));
    */

    layout->addWidget(welcomeLabel);
    layout->addWidget(hintLabel);
    //layout->addWidget(timeLabel);

    stackedWidget->addWidget(startTab);
}

void MainWindow::setupToDoListTab() {
    QWidget *toDoListTab = new QWidget();
    QVBoxLayout *toDoListLayout = new QVBoxLayout(toDoListTab);

    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);

    QWidget *scrollContent = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setAlignment(Qt::AlignTop);

    toDoList->refreshList(scrollLayout);
    scrollArea->setWidget(scrollContent);

    toDoListLayout->addWidget(scrollArea);
    stackedWidget->addWidget(toDoListTab);
}

void MainWindow::setupImPomodoroTab() {
    QWidget* imPomodoroTab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(imPomodoroTab);

    imPomodoroScrollArea = new QScrollArea();
    imPomodoroScrollArea->setWidgetResizable(true);

    QWidget* scrollContent = new QWidget();
    imPomodoroScrollLayout = new QVBoxLayout(scrollContent);
    imPomodoroScrollLayout->setAlignment(Qt::AlignTop);

    pomodoroList->refreshList(imPomodoroScrollLayout);
    imPomodoroScrollArea->setWidget(scrollContent);

    layout->addWidget(imPomodoroScrollArea);
    stackedWidget->addWidget(imPomodoroTab);
}

void MainWindow::setupPomodoroTab() {
    QWidget *pomodoroTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(pomodoroTab);

    classicPomodoro = new ClassicPomodoro();//konstruktor!
    classicPomodoro->timer = new Timer;

    //--------------------------------------
    classicPomodoro->changeProperties(5*60,5*60,5*60,5);
    classicPomodoro->setCurrentPhase("Work");
    //--------------------------------------

    classicPomodoro->timer->setTime(classicPomodoro->getWorkDuration());

    classicPomodoro->timer->timeLabel->setStyleSheet(
        "font-size: 60px; "
        "font-weight: bold; "
        "color: #3a3a3a ; "
        "background-color: #ff99cc; "
        "border: 2px solid #000000; "
        "border-radius: 15px; "
        "padding: 20px; "
        "margin: 20px;"
        );
    classicPomodoro->timer->timeLabel->setAlignment(Qt::AlignCenter);

    QString buttonStyle =
        "QPushButton {"
        "   font-size: 16px; "
        "   padding: 10px 20px; "
        "   border-radius: 5px; "
        "   background-color: #ff66cc; "
        "   color: #3a3a3a; "
        "   margin: 5px; "
        "}"
        "QPushButton:hover { background-color: #cc3399; }";

    classicPomodoro->timer->startButton->setStyleSheet(buttonStyle);
    classicPomodoro->timer->pauseButton->setStyleSheet(buttonStyle);
    classicPomodoro->timer->resetButton->setStyleSheet(buttonStyle);

    QLabel *phaseLabel = new QLabel("Current phase: " + classicPomodoro->getcurrentPhase());
    phaseLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(classicPomodoro->timer->startButton);
    buttonLayout->addWidget(classicPomodoro->timer->pauseButton);
    buttonLayout->addWidget(classicPomodoro->timer->resetButton);

    layout->addWidget(phaseLabel, 0, Qt::AlignCenter);
    layout->addWidget(classicPomodoro->timer->timeLabel, 0, Qt::AlignCenter);
    layout->addLayout(buttonLayout);
    layout->addStretch();

    stackedWidget->addWidget(pomodoroTab);
}

void MainWindow::setupStatisticsTab() {
    QWidget *statsTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(statsTab);
    QLabel *label = new QLabel("Work in progress");

    label->setStyleSheet(
        "font-family: 'Freestyle Script'; "
        "font-size: 40px; "
        "font-weight: bold; "
        "color: #fce4ec; "
        "letter-spacing: 2px; "
        "background-color: #000000; "
        "border-radius: 10px; "
        "padding: 10px;"
        );

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    stackedWidget->addWidget(statsTab);
}

void MainWindow::setupSettingsTab() {
    QWidget *settingsTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(settingsTab);
    QLabel *label = new QLabel("Work in progress");

    label->setStyleSheet(
        "font-family: 'Freestyle Script'; "
        "font-size: 40px; "
        "font-weight: bold; "
        "color: #fce4ec; "
        "letter-spacing: 2px; "
        "background-color: #000000; "
        "border-radius: 10px; "
        "padding: 10px;"
        );

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    stackedWidget->addWidget(settingsTab);
}

QPushButton* MainWindow::createMenuButton() {
    QMenu *menu = new QMenu(this);

    QAction *startAction = new QAction("Home", this);
    QAction *toDoListAction = new QAction("ToDo List", this);
    QAction *imPomodoroAction = new QAction("ImPomodoro", this);
    QAction *pomodoroAction = new QAction("Pomodoro", this);
    QAction *statsAction = new QAction("Statistics", this);
    QAction *settingsAction = new QAction("Settings", this);

    menu->addAction(startAction);
    menu->addAction(toDoListAction);
    menu->addAction(imPomodoroAction);
    menu->addAction(pomodoroAction);
    menu->addAction(statsAction);
    menu->addAction(settingsAction);

    connect(startAction, &QAction::triggered, this, &MainWindow::showHomeTab);
    connect(toDoListAction, &QAction::triggered, this, &MainWindow::showToDoList);
    connect(imPomodoroAction, &QAction::triggered, this, &MainWindow::showImPomodoro);
    connect(pomodoroAction, &QAction::triggered, this, &MainWindow::showPomodoro);
    connect(statsAction, &QAction::triggered, this, &MainWindow::showStatistics);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::showSettings);

    QPushButton *menuButton = new QPushButton("Menu", this);
    menuButton->setMenu(menu);
    menuButton->setFixedSize(100, 40);

    return menuButton;
}

void MainWindow::showHomeTab() {
    stackedWidget->setCurrentIndex(0);
    addButton->hide();
}

void MainWindow::showToDoList() {
    stackedWidget->setCurrentIndex(1);
    addButton->show();
}

void MainWindow::showImPomodoro() {
    stackedWidget->setCurrentIndex(2);
    addButton->show();
}

void MainWindow::showPomodoro() {
    stackedWidget->setCurrentIndex(3);
    addButton->hide();
}

void MainWindow::showStatistics() {
    stackedWidget->setCurrentIndex(4);
    addButton->hide();
}

void MainWindow::showSettings() {
    stackedWidget->setCurrentIndex(5);
    addButton->hide();
}

void MainWindow::addTaskField() {
    if(stackedWidget->currentIndex() == 1) {
        // Dodaj nowe zadanie
        Task* task = TaskFactory::createTask("Basic", "...");
        toDoList->addTask(task);

        QWidget* currentWidget = qobject_cast<QWidget*>(scrollArea->widget());
        if (currentWidget) {
            QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(currentWidget->layout());
            if (layout)
                toDoList->refreshList(layout);
        }
    //--------- Debug --------------------------------
        QList<Task*> currentTasks = toDoList->getTasks();
        qDebug() << "=== TO DO LIST ===";
        for (Task* t : currentTasks)
            qDebug() << "- " << t->getName();
    //------------------------------------------------

    } else if(stackedWidget->currentIndex() == 2) {
        Task* baseTask = TaskFactory::createTask("Pomodoro", "...", 25);
        PomodoroTask* task = dynamic_cast<PomodoroTask*>(baseTask);
        pomodoroList->addTask(task);

        QWidget* currentWidget = qobject_cast<QWidget*>(imPomodoroScrollArea->widget());
        if (currentWidget) {
            QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(currentWidget->layout());
            if (layout)
                pomodoroList->refreshList(layout);
        }
    }
}
