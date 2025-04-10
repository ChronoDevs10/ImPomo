QT += core gui sql
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    appsettings.cpp \
    classicpomodoro.cpp \
    extendedpomodoro.cpp \
    main.cpp \
    mainwindow.cpp \
    notifications.cpp \
    pomodorolist.cpp \
    pomodorotask.cpp \
    statistics.cpp \
    task.cpp \
    taskfactory.cpp \
    testClassicPomodoro.cpp \
    testExtendedPomodoro.cpp \
    testNotifications.cpp \
    testPomodoroList.cpp \
    testPomodoroTask.cpp \
    testSettings.cpp \
    testStatistics.cpp \
    testTask.cpp \
    testTaskFactory.cpp \
    testTimer.cpp \
    testToDoList.cpp \
    timer.cpp \
    todolist.cpp


HEADERS += \
    appsettings.h \
    classicpomodoro.h \
    extendedpomodoro.h \
    ipomodoromode.h \
    itasklist.h \
    itimer.h \
    itimerobserver.h \
    mainwindow.h \
    notifications.h \
    pomodorolist.h \
    pomodorotask.h \
    statistics.h \
    task.h \
    taskfactory.h \
    timer.h \
    todolist.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    tst_task.qml
