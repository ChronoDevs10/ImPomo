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
#include <QDialog>
#include <QSpinBox>
#include <QLineEdit>
#include <QApplication>
#include <QApplication>
#include <QPushButton>
#include <QScreen>

#include <QDialogButtonBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), toDoList(new ToDoList()),
    pomodoroList(new PomodoroList()), classicPomodoro(new ClassicPomodoro()), extendedPomodoro(new ExtendedPomodoro(pomodoroList)),
    taskIdx(0)
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
    addButton->setStyleSheet("QPushButton { border-radius: 5px; background-color: #ff99cc; color: white; font: bold 24px; }");
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addTaskField);
    mainLayout->addWidget(addButton, 0, Qt::AlignHCenter);

    setWindowTitle("✨ImPomo✨");
    resize(600, 800);
}

MainWindow::~MainWindow() {
    delete toDoList;
    delete pomodoroList;
    delete classicPomodoro;
    delete extendedPomodoro;
}

void MainWindow::setupHomeTab() {
    QWidget *startTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(startTab);

    QLabel *welcomeLabel = new QLabel("Welcome to ✨ImPomo✨");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 60px; font-weight: bold;");

    QLabel *hintLabel = new QLabel("Select a tab from the menu to get started");
    hintLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(welcomeLabel);
    layout->addWidget(hintLabel);

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
    QHBoxLayout* mainLayout = new QHBoxLayout(imPomodoroTab);

    imPomodoroScrollArea = new QScrollArea();
    imPomodoroScrollArea->setWidgetResizable(true);

    QWidget* scrollContent = new QWidget();
    imPomodoroScrollLayout = new QVBoxLayout(scrollContent);
    imPomodoroScrollLayout->setAlignment(Qt::AlignTop);

    pomodoroList->refreshList(imPomodoroScrollLayout);
    imPomodoroScrollArea->setWidget(scrollContent);

    mainLayout->addWidget(imPomodoroScrollArea, 1);

    QWidget* timeWidget = new QWidget();
    QVBoxLayout* timeLayout = new QVBoxLayout(timeWidget);

    //-------------------------------------------------------------------------------------------------
    extendedPomodoro->timer->timeLabel->setStyleSheet(
        "font-size: 100px; "
        "font-weight: bold; "
        "color: #3a3a3a ; "
        "background-color: #ff99cc; "
        "border: 2px solid #000000; "
        "border-radius: 30px; "
        "padding: 50px 90px; "
        "margin: 20px;"
        );

    QString buttonStyle =
        "QPushButton {"
        "   font-size: 25px; "
        "   padding: 30px 35px; "
        "   border-radius: 5px; "
        "   background-color: #ff66cc; "
        "   color: #3a3a3a; "
        "   margin: 5px; "
        "}"
        "QPushButton:hover { background-color: #cc3399; }";

    extendedPomodoro->timer->startButton->setStyleSheet(buttonStyle);
    extendedPomodoro->timer->pauseButton->setStyleSheet(buttonStyle);
    extendedPomodoro->timer->resetButton->setStyleSheet(buttonStyle);
    //-------------------------------------------------------------------------------------------------
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(extendedPomodoro->timer->startButton);
    buttonLayout->addWidget(extendedPomodoro->timer->pauseButton);
    buttonLayout->addWidget(extendedPomodoro->timer->resetButton);

    timeLayout->addStretch(1);
    timeLayout->addWidget(extendedPomodoro->currTaskLabel, 0, Qt::AlignCenter);
    timeLayout->addWidget(extendedPomodoro->timer->timeLabel, 0, Qt::AlignCenter);
    extendedPomodoro->timer->timeLabel->setAlignment(Qt::AlignCenter);
    timeLayout->addLayout(buttonLayout);
    timeLayout->addStretch(1);
    mainLayout->addWidget(timeWidget, 1);


    stackedWidget->addWidget(imPomodoroTab);
}

void MainWindow::setupPomodoroTab() {
    QWidget *pomodoroTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(pomodoroTab);

    QPushButton *settingsButton = new QPushButton("⚙️");
    settingsButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 30px; "
        "   padding: 10px 10px; "
        "   border-radius: 10px; "
        "   background-color: #ff99cc; "
        "   color: #3a3a3a; "
        "}"
        "QPushButton:hover { background-color: #cc3399; }");
    settingsButton->setFixedSize(60, 60);
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::PomodoroSettings);

    //--------------------------------------------------------------------------------
    //do przeniesienia do konstruktora Timera, jeżeli będzie jednolity styl zegarów
    //w całej aplikacji
    classicPomodoro->timer->timeLabel->setStyleSheet(
        "font-size: 100px; "
        "font-weight: bold; "
        "color: #3a3a3a ; "
        "background-color: #ff99cc; "
        "border: 2px solid #000000; "
        "border-radius: 30px; "
        "padding: 50px 90px; "
        "margin: 20px;"
        );

    QString buttonStyle =
        "QPushButton {"
        "   font-size: 25px; "
        "   padding: 30px 35px; "
        "   border-radius: 5px; "
        "   background-color: #ff66cc; "
        "   color: #3a3a3a; "
        "   margin: 5px; "
        "}"
        "QPushButton:hover { background-color: #cc3399; }";

    classicPomodoro->timer->startButton->setStyleSheet(buttonStyle);
    classicPomodoro->timer->pauseButton->setStyleSheet(buttonStyle);
    classicPomodoro->timer->resetButton->setStyleSheet(buttonStyle);
    //-------------------------------------------------------------------------------------------------

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(classicPomodoro->timer->startButton);
    buttonLayout->addWidget(classicPomodoro->timer->pauseButton);
    buttonLayout->addWidget(classicPomodoro->timer->resetButton);

    layout->addWidget(settingsButton, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(classicPomodoro->phaseLabel, 0, Qt::AlignCenter);
    layout->addWidget(classicPomodoro->timer->timeLabel, 0, Qt::AlignCenter);

    classicPomodoro->timer->timeLabel->setAlignment(Qt::AlignCenter);

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

void MainWindow::PomodoroSettings() {
    QDialog dialog(this);
    dialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    dialog.setWindowTitle("Pomodoro Settings");
    dialog.setFixedSize(400, 400);

    QString style =
        "QDialog {"
        "   background-color: #121212;"
        "   color: #ffffff;"
        "   font-family: 'Segoe UI', sans-serif;"
        "   font-size: 14px;"
        "}"

        "QLabel {"
        "   color: #ffb6c1;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   margin-top: 10px;"
        "}"

        "QLineEdit {"
        "   background-color: #1e1e1e;"
        "   color: #ffffff;"
        "   border: 1px solid #ffb6c1;"
        "   border-radius: 5px;"
        "   padding: 4px;"
        "   min-width: 120px;"
        "   height: 40px;"
        "}"

        "QDialogButtonBox QPushButton {"
        "   background-color: #ffb6c1;"
        "   color: #121212;"
        "   padding: 8px 16px;"
        "   border: none;"
        "   border-radius: 6px;"
        "   font-weight: bold;"
        "   min-width: 80px;"
        "}"

        "QDialogButtonBox QPushButton:hover {"
        "   background-color: #ff8da1;"
        "}"

        "QDialogButtonBox QPushButton:pressed {"
        "   background-color: #ff6b8b; "
        "}";
    dialog.setStyleSheet(style);

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QLineEdit* workLineEdit = new QLineEdit();
    workLineEdit->setText(QString::number(classicPomodoro->getWorkDuration()));
    workLineEdit->setValidator(new QIntValidator(1, 120));
    layout->addWidget(new QLabel("Work duration (min):"));
    layout->addWidget(workLineEdit);

    QLineEdit* shortBreakLineEdit = new QLineEdit();
    shortBreakLineEdit->setText(QString::number(classicPomodoro->getShortBreakDuration()));
    shortBreakLineEdit->setValidator(new QIntValidator(1, 60));
    layout->addWidget(new QLabel("Short break (min):"));
    layout->addWidget(shortBreakLineEdit);

    QLineEdit* longBreakLineEdit = new QLineEdit();
    longBreakLineEdit->setText(QString::number(classicPomodoro->getLongBreakDuration()));
    longBreakLineEdit->setValidator(new QIntValidator(1, 60));
    layout->addWidget(new QLabel("Long break (min):"));
    layout->addWidget(longBreakLineEdit);

    QLineEdit* cyclesLineEdit = new QLineEdit();
    cyclesLineEdit->setText(QString::number(classicPomodoro->getCycles()));
    cyclesLineEdit->setValidator(new QIntValidator(1, 15));
    layout->addWidget(new QLabel("Number of cycles:"));
    layout->addWidget(cyclesLineEdit);

    QLineEdit* workBlocksLineEdit = new QLineEdit();
    workBlocksLineEdit->setText(QString::number(classicPomodoro->getWorkBlocks()));
    workBlocksLineEdit->setValidator(new QIntValidator(1, 15));
    layout->addWidget(new QLabel("Number of work blocks per cycle:"));
    layout->addWidget(workBlocksLineEdit);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if(dialog.exec() == QDialog::Accepted) {
        classicPomodoro->changeProperties(
            workLineEdit->text().toInt(),
            shortBreakLineEdit->text().toInt(),
            longBreakLineEdit->text().toInt(),
            cyclesLineEdit->text().toInt(),
            workBlocksLineEdit->text().toInt()
            );
    }
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
        Task* task = TaskFactory::createTask("Basic", "");
        toDoList->addTask(task);

        QWidget* currentWidget = qobject_cast<QWidget*>(scrollArea->widget());
        if(currentWidget) {
            QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(currentWidget->layout());
            if(layout)
                toDoList->refreshList(layout);
        }

    } else if(stackedWidget->currentIndex() == 2) {
        QString taskIdxStr = QString::number(taskIdx);
        Task* baseTask = TaskFactory::createTask("Pomodoro", taskIdxStr, 5);
        taskIdx++;
        PomodoroTask* task = dynamic_cast<PomodoroTask*>(baseTask);
        extendedPomodoro->list->addTask(task);

        QWidget* currentWidget = qobject_cast<QWidget*>(imPomodoroScrollArea->widget());
        if(currentWidget) {
            QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(currentWidget->layout());
            if(layout)
                extendedPomodoro->list->refreshList(layout);
        }
    }
}
