#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), toDoList(new ToDoList()), pomodoroList(new PomodoroList()),
    classicPomodoro(new ClassicPomodoro()), extendedPomodoro(new ExtendedPomodoro(pomodoroList)),
    appSettings(new AppSettings()), statistics(new Statistics()), notifications(new Notifications())
{

    appSettings->loadSettingsFromFile();
    notifications->settings = appSettings;

    statistics->appSettings = appSettings;
    toDoList->loadFromDatabase();
    toDoList->settings = appSettings;

    pomodoroList->settings = appSettings;

    extendedPomodoro->settings = appSettings;
    extendedPomodoro->notifications = notifications;
    extendedPomodoro->loadSessionStateFromFile();
    extendedPomodoro->loadFromDatabase();
    extendedPomodoro->stats = statistics;

    classicPomodoro->notifications = notifications;
    classicPomodoro->stats = statistics;
    classicPomodoro->loadSettingsFromFile();
    classicPomodoro->loadSessionStateFromFile();

    //-----------------------------------------------
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
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addTaskField);
    mainLayout->addWidget(addButton, 0, Qt::AlignHCenter);

    setWindowTitle("ImPomo");
    showMaximized();

    if(appSettings->getTheme() == "Light") {
        setStyle(0);
    } else if(appSettings->getTheme()  == "Dark")
        setStyle(1);
}

MainWindow::~MainWindow() {
    delete toDoList;
    delete pomodoroList;
    delete classicPomodoro;
    delete extendedPomodoro;
    delete appSettings;
    delete notifications;
    delete statistics;
}

void MainWindow::setupHomeTab() {
    QWidget *startTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(startTab);

    QLabel *welcomeLabel = new QLabel("Welcome to ✨ImPomo✨");
    welcomeLabel->setObjectName("Welcome label");
    welcomeLabel->setAlignment(Qt::AlignCenter);

    QLabel *hintLabel = new QLabel("Select a tab from the menu to get started");
    hintLabel->setObjectName("hint");
    hintLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(welcomeLabel);
    layout->addWidget(hintLabel);

    stackedWidget->addWidget(startTab);
    setStyleHome(1);
}

void MainWindow::setupToDoListTab() {
    QWidget *toDoListTab = new QWidget();
    QVBoxLayout *toDoListLayout = new QVBoxLayout(toDoListTab);

    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);

    QWidget *scrollContent = new QWidget();
    scrollContent->setObjectName("toDoScrollContent");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setObjectName("scrollLayout");
    scrollLayout->setAlignment(Qt::AlignTop);

    toDoList->refreshList(scrollLayout);
    scrollArea->setWidget(scrollContent);

    toDoListLayout->addWidget(scrollArea);
    stackedWidget->addWidget(toDoListTab);

    setStyleToDo(1);
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

    QPushButton* resetAllButton = new QPushButton("Clear All Tasks");
    resetAllButton->setObjectName("resetAllButton");

    timeLayout->addWidget(resetAllButton, 0, Qt::AlignRight);

    QObject::connect(resetAllButton, &QPushButton::clicked, [this]() {
        extendedPomodoro->clearAllTasks();
        pomodoroList->refreshList(imPomodoroScrollLayout);
    });

    mainLayout->addWidget(timeWidget, 1);

    stackedWidget->addWidget(imPomodoroTab);
    setStyleImPomo(1);
}

void MainWindow::setupPomodoroTab() {
    QWidget *pomodoroTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(pomodoroTab);

    QPushButton *settingsButton = new QPushButton("⚙️");

    settingsButton->setFixedSize(60, 60);
    settingsButton->setObjectName("settingsButton");
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::PomodoroSettings);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(classicPomodoro->timer->startButton);
    buttonLayout->addWidget(classicPomodoro->timer->pauseButton);
    buttonLayout->addWidget(classicPomodoro->timer->resetButton);


    layout->addWidget(settingsButton, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(classicPomodoro->phaseLabel, 0, Qt::AlignCenter);
    layout->addWidget(classicPomodoro->timer->timeLabel, 0, Qt::AlignCenter);

    classicPomodoro->timer->timeLabel->setAlignment(Qt::AlignCenter);

    layout->addLayout(buttonLayout);
    QPushButton* reset = new QPushButton("Reset Pomodoro");
    reset->setObjectName("reset");

    layout->addWidget(reset, 0, Qt::AlignRight);

    QObject::connect(reset, &QPushButton::clicked, [this]() {
        classicPomodoro->resetPomodoro();
    });
    layout->addStretch();

    stackedWidget->addWidget(pomodoroTab);
    setStyleClassPomo(1);
}

void MainWindow::setupStatisticsTab() {
    QWidget* statsTab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(statsTab);

    QLabel* titleLabel = new QLabel("Choose a day to view the report");
    titleLabel->setObjectName("titleLabel");
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    layout->addWidget(titleLabel, 0, Qt::AlignTop);

    QCalendarWidget* calendar = new QCalendarWidget();
    calendar->setObjectName("calendar");
    calendar->setGridVisible(true);
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendar->setLocale(QLocale(QLocale::English));

    layout->addWidget(calendar, 1);

    connect(calendar, &QCalendarWidget::clicked, this, [=](const QDate& date) {
        statistics->displayReport(date);
    });

    stackedWidget->addWidget(statsTab);
    setStyleStats(1);
}

void MainWindow::setupSettingsTab() {
    QWidget *settingsTab = new QWidget();

    QVBoxLayout *outerLayout = new QVBoxLayout(settingsTab);
    outerLayout->setContentsMargins(50, 50, 50, 50);
    outerLayout->setAlignment(Qt::AlignCenter);

    QWidget *container = new QWidget();
    container->setObjectName("settingsContainer");

    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setSpacing(15);
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    QCheckBox *soundToggle = new QCheckBox("Sound notifications");
    soundToggle->setChecked(appSettings->getSoundStatus());
    layout->addWidget(soundToggle);

    connect(soundToggle, &QCheckBox::toggled, this, [=](bool checked) {
        appSettings->setSoundStatus(checked);
        appSettings->saveSettingsToFile();
    });

    QComboBox *soundComboBox = new QComboBox();
    soundComboBox->addItem("Soft Alarm");
    soundComboBox->addItem("Fanfares");

    QLabel *soundLabel = new QLabel("Select sound:");
    layout->addWidget(soundLabel);
    layout->addWidget(soundComboBox);

    int soundIndex = soundComboBox->findText(appSettings->getSoundType());
    soundComboBox->setCurrentIndex(soundIndex >= 0 ? soundIndex : 0);

    connect(soundComboBox, &QComboBox::currentTextChanged, this, [=](const QString &text) {
        appSettings->setSound(text);
        notifications->playSound();
        appSettings->saveSettingsToFile();
    });

    QGroupBox *themeGroup = new QGroupBox("Theme");
    QVBoxLayout *themeLayout = new QVBoxLayout(themeGroup);

    QRadioButton *lightTheme = new QRadioButton("Light");
    QRadioButton *darkTheme = new QRadioButton("Dark");

    themeLayout->addWidget(darkTheme);
    themeLayout->addWidget(lightTheme);

    QString currentTheme = appSettings->getTheme();
    if(currentTheme == "Light")
        lightTheme->setChecked(true);
    else
        darkTheme->setChecked(true);

    layout->addWidget(themeGroup);

    connect(lightTheme, &QRadioButton::toggled, this, [=](bool checked) {
        if(checked) {
            appSettings->setTheme("Light");
            appSettings->saveSettingsToFile();
            setStyle(0);
        }
    });
    connect(darkTheme, &QRadioButton::toggled, this, [=](bool checked) {
        if(checked) {
            appSettings->setTheme("Dark");
            appSettings->saveSettingsToFile();
            setStyle(1);
        }
    });

    layout->addStretch();

    outerLayout->addWidget(container);
    stackedWidget->addWidget(settingsTab);
    settingsTab->setObjectName("settingsTab");

    setStyleSett(1);
}

void MainWindow::PomodoroSettings() {
    QDialog dialog(this);
    dialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    dialog.setWindowTitle("Pomodoro Settings");
    dialog.setFixedSize(400, 400);

    QString style;

    if(appSettings->getTheme() == "Light")
        style = "QDialog { background-color: #ffd59a; color: #000000; font-family: 'Segoe UI', sans-serif; font-size: 14px; border: 1px solid #4c4c4c; border-radius: 5px; padding: 5px; }\n" \
            "QLabel { color: #000000; font-size: 16px; font-weight: bold; margin-top: 10px; }\n" \
            "QLineEdit { background-color: #fff1db; color: #000000; border: 1px solid #4c4c4c; border-radius: 5px; padding: 4px; min-width: 120px; height: 40px; }\n" \
            "QDialogButtonBox QPushButton { background-color: #ffb74d; color: #000000; padding: 8px 16px; border: 1px solid #e0912d; border-radius: 6px; font-weight: bold; min-width: 80px; }\n" \
            "QDialogButtonBox QPushButton:hover { background-color: #ffa726; }\n" \
            "QDialogButtonBox QPushButton:pressed { background-color: #fb8c00; }\n";
    else if(appSettings->getTheme() == "Dark")
        style = "QDialog { background-color: #000000; color: #ffffff; font-family: 'Segoe UI', sans-serif; font-size: 14px; border: 1px solid #5f5f5f; border-radius: 5px; padding: 5px; }\n" \
            "QLabel { color: #d0d0d0; font-size: 16px; font-weight: bold; margin-top: 10px; }\n" \
            "QLineEdit { background-color: #1a1a1a; color: #ffffff; border: 1px solid #7f7f7f; border-radius: 5px; padding: 4px; min-width: 120px; height: 40px; }\n" \
            "QDialogButtonBox QPushButton { background-color: #5f5f5f; color: #ffffff; padding: 8px 16px; border: none; border-radius: 6px; font-weight: bold; min-width: 80px; }\n" \
            "QDialogButtonBox QPushButton:hover { background-color: #7a7a7a; }\n" \
            "QDialogButtonBox QPushButton:pressed { background-color: #9a9a9a; }\n";
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
        classicPomodoro->saveSettingsToFile();
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
        Task* baseTask = TaskFactory::createTask("Pomodoro", "", 25);
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

void MainWindow::setStyleHome(int style) {
    QWidget* tab = stackedWidget->widget(0);
    QLabel* welcomelabel = tab->findChild<QLabel*>("Welcome label");
    QLabel* hint = tab->findChild<QLabel*>("hint");

    if(style == 0) {
        tab->setStyleSheet("background-color: #ffecb3;");
        welcomelabel->setStyleSheet("font-size: 60px; font-weight: bold; color: black;");
        hint->setStyleSheet("font-size: 20px; color: black;");
    } else if(style == 1) {
        tab->setStyleSheet("background-color: #1f1f1f;");
        welcomelabel->setStyleSheet("font-size: 60px; font-weight: bold; color: white;");
        hint->setStyleSheet("font-size: 20px; color: white;");
    }
}
void MainWindow::setStyleToDo(int style) {
    QWidget* tab = stackedWidget->widget(1);
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(tab->layout());
    QVBoxLayout* refreshTasks = scrollArea->findChild<QVBoxLayout*>("scrollLayout");

    if(style == 0)
        tab->setStyleSheet("background-color: #ffecb3;");
    else if(style == 1)
        tab->setStyleSheet("background-color: #1f1f1f;");

    toDoList->refreshList(refreshTasks);
}
void MainWindow::setStyleImPomo(int style) {
    QWidget* tab = stackedWidget->widget(2);
    QPushButton* resetAllButton = tab->findChild<QPushButton*>("resetAllButton");
    QString TimerStyle;
    QString TimerButtonStyle;

    if(style == 0) {
        tab->setStyleSheet("background-color: #ffecb3;");
        extendedPomodoro->currTaskLabel->setStyleSheet("font-size: 25px; font-weight: bold; color: black; margin: 10px;");
        TimerStyle = getTimerStyle(0);
        TimerButtonStyle = getTimerButtonStyle(0);

        resetAllButton->setStyleSheet("QPushButton {font-size: 20px; padding: 15px 20px; border-radius: 5px; "
        "background-color: #ffb74d; color: black; margin: 10px; border: 1px solid #4c4c4c;} QPushButton:hover { background-color: #ffa726; }");
    } else if(style == 1) {
        tab->setStyleSheet("background-color: #1f1f1f;");
        extendedPomodoro->currTaskLabel->setStyleSheet("font-size: 25px; font-weight: bold; color: white; margin: 10px;");
        TimerStyle = getTimerStyle(1);
        TimerButtonStyle = getTimerButtonStyle(1);
        resetAllButton->setStyleSheet(
            "QPushButton {"
            "   font-size: 20px; "
            "   padding: 15px 20px; "
            "   border-radius: 5px; "
            "   background-color: #ff3333; "
            "   color: white; "
            "   margin: 10px; "
            "   border: 1px solid #5f5f5f;"
            "}"
            "QPushButton:hover { background-color: #cc3333; }"
        );
    }
    extendedPomodoro->timer->startButton->setStyleSheet(TimerButtonStyle);
    extendedPomodoro->timer->pauseButton->setStyleSheet(TimerButtonStyle);
    extendedPomodoro->timer->resetButton->setStyleSheet(TimerButtonStyle);
    extendedPomodoro->timer->timeLabel->setStyleSheet(TimerStyle);

    pomodoroList->refreshList(imPomodoroScrollLayout);
}
void MainWindow::setStyleClassPomo(int style) {
    QWidget* tab = stackedWidget->widget(3);
    QPushButton* settingsButton = tab->findChild<QPushButton*>("settingsButton");
    QPushButton* reset = tab->findChild<QPushButton*>("reset");
    QString TimerStyle;
    QString TimerButtonStyle;

    if(style == 0) {
        tab->setStyleSheet("background-color: #ffecb3;");
        classicPomodoro->phaseLabel->setStyleSheet("font-size: 25px; font-weight: bold; color: black; margin: 10px;");
        TimerStyle = getTimerStyle(0);
        TimerButtonStyle = getTimerButtonStyle(0);
        settingsButton->setStyleSheet(
            "QPushButton {"
            "   font-size: 30px; "
            "   padding: 10px 10px; "
            "   border-radius: 10px; "
            "   border: 1px solid #4c4c4c;"
            "   background-color: #ffb74d; "
            "   color: #000000; "
            "}"
            "QPushButton:hover { background-color: #ffa726; }"
            );
        reset->setStyleSheet("QPushButton {font-size: 20px; padding: 15px 20px; border-radius: 5px; "
                                      "background-color: #ffb74d; color: black; margin: 10px; border: 1px solid #4c4c4c;} QPushButton:hover { background-color: #ffa726; }");
    } else if(style == 1) {
        tab->setStyleSheet("background-color: #1f1f1f;");
        classicPomodoro->phaseLabel->setStyleSheet("font-size: 25px; font-weight: bold; color: white; margin: 10px;");
        TimerStyle = getTimerStyle(1);
        TimerButtonStyle = getTimerButtonStyle(1);
        settingsButton->setStyleSheet(
            "QPushButton {"
            "   font-size: 30px; "
            "   padding: 10px 10px; "
            "   border-radius: 10px; "
            "   background-color: #555555; "
            "   color: #e0e0e0; "
            "}"
            "QPushButton:hover { background-color: #777777; }");

        reset->setStyleSheet(
            "QPushButton {"
            "   font-size: 20px; "
            "   padding: 15px 20px; "
            "   border-radius: 5px; "
            "   background-color: #ff3333; "
            "   color: white; "
            "   margin: 10px; "
            "   border: 1px solid #5f5f5f;"
            "}"
            "QPushButton:hover { background-color: #cc3333; }"
            );
    }
    classicPomodoro->timer->startButton->setStyleSheet(TimerButtonStyle);
    classicPomodoro->timer->pauseButton->setStyleSheet(TimerButtonStyle);
    classicPomodoro->timer->resetButton->setStyleSheet(TimerButtonStyle);
    classicPomodoro->timer->timeLabel->setStyleSheet(TimerStyle);

    tab->style()->unpolish(tab);
    tab->style()->polish(tab);
    tab->update();

}
void MainWindow::setStyleStats(int style) {
    QWidget* tab = stackedWidget->widget(4);
    QCalendarWidget* calendar = tab->findChild<QCalendarWidget*>("calendar");
    QLabel* titleLabel =tab->findChild<QLabel*>("titleLabel");

    if(style == 0) {
        tab->setStyleSheet("background-color: #ffecb3;");
        titleLabel->setStyleSheet("font-size: 25px; font-weight: bold; color: black; margin: 10px;");
        calendar->setStyleSheet(
            "QCalendarWidget {"
            "   border: 2px solid #4c4c4c;"
            "   border-radius: 8px;"
            "   background-color: #fff0db;"
            "   color: #000000;"
            "}"
            "QCalendarWidget QWidget#qt_calendar_navigationbar {"
            "   background-color: #ffe0b2;"
            "}"
            "QCalendarWidget QToolButton {"
            "   background-color: #ffb74d;"
            "   color: #000000;"
            "   font-size: 18px;"
            "   padding: 8px 12px;"
            "   border-radius: 5px;"
            "}"
            "QCalendarWidget QToolButton:hover {"
            "   background-color: #ffa726;"
            "}"
            "QCalendarWidget QToolButton#qt_calendar_prevmonth,"
            "QCalendarWidget QToolButton#qt_calendar_nextmonth {"
            "   background-color: transparent;"
            "   border: none;"
            "}"
            "QCalendarWidget QMenu {"
            "   background-color: #fff5e6;"
            "   color: #000000;"
            "}"
            "QCalendarWidget QAbstractItemView {"
            "   background-color: #fff9ec;"
            "   font-size: 20px;"
            "   border-radius: 5px;"
            "   color: #000000;"
            "}"
            "QCalendarWidget QAbstractItemView::item:enabled {"
            "   color: #000000;"
            "}"
            "QCalendarWidget QAbstractItemView::item:disabled {"
            "   background-color: #f0e0d0;"
            "   color: #999999;"
            "}"
            "QCalendarWidget QAbstractItemView::item:hover {"
            "   background-color: #ffd180;"
            "   color: #000000;"
            "}"
            );
    } else if(style == 1) {
        tab->setStyleSheet("background-color: #1f1f1f;");
        titleLabel->setStyleSheet("font-size: 25px; font-weight: bold; color: white; margin: 10px;");
        calendar->setStyleSheet(
            "QCalendarWidget {"
            "   border: 2px solid #5f5f5f;"
            "   border-radius: 8px;"
            "   background-color: #121212;"
            "   color: #e0e0e0;"
            "}"
            "QCalendarWidget QWidget#qt_calendar_navigationbar {"
            "   background-color: #1a1a1a;"
            "}"
            "QCalendarWidget QToolButton {"
            "   background-color: #2a2a2a;"
            "   color: #f0f0f0;"
            "   font-size: 18px;"
            "   padding: 8px 12px;"
            "   border-radius: 5px;"
            "}"
            "QCalendarWidget QToolButton:hover {"
            "   background-color: #3a3a3a;"
            "}"
            "QCalendarWidget QToolButton#qt_calendar_prevmonth,"
            "QCalendarWidget QToolButton#qt_calendar_nextmonth {"
            "   background-color: transparent;"
            "   border: none;"
            "}"
            "QCalendarWidget QMenu {"
            "   background-color: #1e1e1e;"
            "   color: #e0e0e0;"
            "}"
            "QCalendarWidget QAbstractItemView {"
            "   background-color: #1e1e1e;"
            "   font-size: 20px;"
            "   border-radius: 5px;"
            "   color: #e0e0e0;"
            "}"
            "QCalendarWidget QAbstractItemView::item:enabled {"
            "   color: #e0e0e0;"
            "}"
            "QCalendarWidget QAbstractItemView::item:disabled {"
            "   background-color: #2a2a2a;"
            "   color: #777777;"
            "}"
            "QCalendarWidget QAbstractItemView::item:hover {"
            "   background-color: #444444;"
            "   color: #ffffff;"
            "}"
            );
    }
}
void MainWindow::setStyleSett(int style) {
    QWidget* tab = stackedWidget->widget(5);

    if(style == 0) {
        tab->setStyleSheet("QWidget#settingsTab { background-color: #fff3db; }"
                           "#settingsContainer { background-color: #ffe0b2; border: 5px solid #a65c00; border-radius: 10px; padding: 80px; }"
                           "QCheckBox, QLabel, QRadioButton { color: #2e1c00; font-size: 28px; font-weight: 800; }"
                           "QComboBox { font-size: 28px; color: #2e1c00; background-color: #fff3db; border: 4px solid #a65c00; border-radius: 12px; padding: 12px 20px; min-width: 280px; }"
                           "QComboBox QAbstractItemView { background-color: #ffe0b2; color: #2e1c00; selection-background-color: #ffb74d; selection-color: black; font-size: 26px; }"
                           "QGroupBox { font-size: 34px; font-weight: 900; color: #a65c00; margin-top: 35px; margin-bottom: 35px; padding: 12px 20px 20px 20px; background: transparent; border: 3px solid #a65c00; border-radius: 25px; subcontrol-origin: margin; subcontrol-position: top center; }"
                           "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top center; padding: 0 12px; background-color: #ffe0b2; color: #a65c00; }"
                           "QRadioButton::indicator, QCheckBox::indicator { width: 20px; height: 20px; border: 2px solid #a65c00; background: #ffffff; }"
                           "QRadioButton::indicator:checked, QCheckBox::indicator:checked { background-color: #ffb74d; border: 2px solid #a65c00; }"
                           "QGroupBox:hover, QGroupBox:focus, QRadioButton:hover, QRadioButton:focus { background: transparent; }");
    } else if(style == 1) {
        tab->setStyleSheet("QWidget#settingsTab { background-color: #111111; }"
                           "#settingsContainer { background-color: #000000; border: 5px solid #5f5f5f; border-radius: 10px; padding: 80px; }"
                           "QCheckBox, QLabel, QRadioButton { color: #f0f0f0; font-size: 28px; font-weight: 800; }"
                           "QComboBox { font-size: 28px; color: #f0f0f0; background-color: #111111; border: 4px solid #5f5f5f; border-radius: 12px; padding: 12px 20px; min-width: 280px; }"
                           "QComboBox QAbstractItemView { background-color: #1a1a1a; color: #f0f0f0; selection-background-color: #444444; selection-color: white; font-size: 26px; }"
                           "QGroupBox { font-size: 34px; font-weight: 900; color: #d0d0d0; margin-top: 35px; margin-bottom: 35px; padding: 12px 20px 20px 20px; background: transparent; border: 3px solid #5f5f5f; border-radius: 25px; subcontrol-origin: margin; subcontrol-position: top center; }"
                           "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top center; padding: 0 12px; background-color: #000000; color: #d0d0d0; }"
                           "QRadioButton::indicator, QCheckBox::indicator { width: 20px; height: 20px; border: 2px solid #5f5f5f; background: #2e2e2e; }"
                           "QRadioButton::indicator:checked, QCheckBox::indicator:checked { background-color: #ffffff; border: 2px solid #5f5f5f; }"
                           "QGroupBox:hover, QGroupBox:focus, QRadioButton:hover, QRadioButton:focus { background: transparent; }");
    }
}
void MainWindow::setStyle(int style) {
    if(style == 0)
        addButton->setStyleSheet("QPushButton { border-radius: 5px; background-color: #fffde7; color: black; font: bold 24px; }");
    else if(style == 1)
        addButton->setStyleSheet("QPushButton { border-radius: 5px; background-color: #2a2a2a; color: white; font-size: 24px; font-weight: 900; }");

    setStyleHome(style);
    setStyleToDo(style);
    setStyleImPomo(style);
    setStyleClassPomo(style);
    setStyleStats(style);
    setStyleSett(style);
}

QString MainWindow::getTimerStyle(int style) {
    if(style == 0) {
        return "font-size: 100px; font-weight: bold; color: black; "
            "background-color: #ffe0b2; border: 1px solid #4c4c4c; "
            "border-radius: 30px; padding: 50px 90px; margin: 20px;";
    } else if(style == 1){
        return
            "font-size: 100px; "
            "font-weight: bold; "
            "color: white; "
            "background-color: #000000; "
            "border: 1px solid #5f5f5f; "
            "border-radius: 30px; "
            "padding: 50px 90px; "
            "margin: 20px;";
    }
}
QString MainWindow::getTimerButtonStyle(int style) {
    if(style == 0) {
        return
            "QPushButton {"
            "   font-size: 25px; "
            "   padding: 30px 35px; "
            "   border-radius: 5px; "
            "   background-color: #ffe0b2; "
            "   color: black; "
            "   border: 1px solid #4c4c4c; "
            "   margin: 5px; "
            "}"
            "QPushButton:hover { background-color: #ffcc80; }";
    } else if(style == 1){
        return
            "QPushButton {"
            "   font-size: 25px; "
            "   padding: 30px 35px; "
            "   border-radius: 5px; "
            "   background-color: #000000; "
            "   color: white; "
            "   border: 1px solid #5f5f5f; "
            "   margin: 5px; "
            "}"
            "QPushButton:hover { background-color: #1a1a1a; }";
    }
}
