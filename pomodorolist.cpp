#include "pomodorolist.h"
#include "extendedpomodoro.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

PomodoroList::PomodoroList() {
    databaseInit();
}

void PomodoroList::addTask(Task* task) {
    PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);
    if(parent != nullptr && tasks.size() == parent->tasksFinished) {
        parent->timer->setTime(pt->getDuration()*60);
        parent->setcurrent(parent->tasksFinished);
    }
    tasks.append(pt);

    if(parent != nullptr)
        parent->updateCurrentTaskLabel();

    saveToDatabase();
}
void PomodoroList::removeTask(Task* task) {
    PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);
    tasks.removeOne(pt);

    saveToDatabase();
}
void PomodoroList::editTaskName(Task* task, QString newName) {
    task->editName(newName);
    if(parent != nullptr)
        parent->updateCurrentTaskLabel();

    saveToDatabase();
}
void PomodoroList::editTaskStatus(Task* task, bool status) {
    task->setStatus(status);
    saveToDatabase();
}
int PomodoroList::taskCount() {
    return tasks.size();
}
QVector<PomodoroTask*> PomodoroList::getPTasks() {
     return tasks;
}
void PomodoroList::reorderTasks(int fromIndex, int toIndex) {
    if(fromIndex < 0 || toIndex < 0 || fromIndex >= tasks.size() || toIndex >= tasks.size())
        return;

    tasks.move(fromIndex, toIndex);

    if(parent != nullptr)
        parent->updateCurrentTaskLabel();
    saveToDatabase();
}
void PomodoroList::editTaskDuration(Task* task, int newDuration) {
    PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);

    pt->editDuration(newDuration);
    if(parent != nullptr)
        parent->timer->updateLabel();
    saveToDatabase();
}

QWidget* PomodoroList::createTaskWidget(PomodoroTask* task) {
    QWidget* fieldWidget = new QWidget();
    QHBoxLayout* inputLayout = new QHBoxLayout(fieldWidget);
    inputLayout->setContentsMargins(10, 10, 10, 10);
    inputLayout->setSpacing(0);

    task->lineEdit = new QLineEdit(task->getName());
    task->lineEdit->setFixedSize(275, 50);
    task->lineEdit->setPlaceholderText("Enter task name");

    QSpinBox* durationBox = new QSpinBox();
    durationBox->setFixedHeight(50);
    durationBox->setFixedWidth(80);
    durationBox->setMinimum(1);
    durationBox->setMaximum(180);
    durationBox->setValue(task->getDuration());
    durationBox->setSuffix(" min");

    QString lineEditStyle;
    QString durationStyle;

    if(settings->getTheme() == "Light") {
        lineEditStyle = "background-color: #ffe0b2; border: 1px solid #4c4c4c; border-radius: 5px; padding: 5px; color: black;";
        durationStyle =
            "QSpinBox {"
            "   font-size: 16px;"
            "   background-color: #ffe0b2;"
            "   border: 1px solid #4c4c4c;"
            "   border-radius: 5px;"
            "   padding: 5px 10px;"
            "   color: black;"
            "}"
            "QSpinBox::up-button, QSpinBox::down-button { width: 0; height: 0; border: none; }";
    } else if(settings->getTheme() == "Dark") {
        lineEditStyle = "background-color: #000000; border: 1px solid #5f5f5f; border-radius: 5px; padding: 5px; color: white;";
        durationStyle =
            "QSpinBox {"
            "   font-size: 16px;"
            "   background-color: #000000;"
            "   border: 1px solid #5f5f5f;"
            "   border-radius: 5px;"
            "   padding: 5px 10px;"
            "   color: white;"
            "}"
            "QSpinBox::up-button, QSpinBox::down-button { width: 0; height: 0; border: none; }";
    }

    durationBox->setStyleSheet(durationStyle);
    task->lineEdit->setStyleSheet(lineEditStyle);
    task->lineEdit->setMaxLength(25);

    QObject::connect(task->lineEdit, &QLineEdit::textChanged, [this, task](const QString& newName) {
        editTaskName(task, newName);
    });

    QObject::connect(durationBox, &QSpinBox::valueChanged, [this, task, durationBox](int newDuration) {
        PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);
        int index = tasks.indexOf(pt);

        if((index > parent->getcurrent()) || (parent->wasStarted == false && index == parent->getcurrent())) {
            editTaskDuration(task, newDuration);
            if(index == parent->getcurrent())
                parent->timer->setTime(task->getDuration()*60);
        }
        else {
            durationBox->blockSignals(true);
            durationBox->setValue(pt->getDuration());
            durationBox->blockSignals(false);
        }
    });

    QPushButton* deleteButton = new QPushButton("🗑");
    deleteButton->setFixedSize(50, 50);

    QObject::connect(deleteButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);
        int index = tasks.indexOf(pt);
        if(!task->getStatus() && (index > parent->getcurrent() || (parent->wasStarted == false && index == parent->getcurrent()))) {
            removeTask(task);
            fieldWidget->deleteLater();
            if(taskCount() == 0) {
                parent->clearAllTasks();
            } else {
                if(tasks.last()->getStatus()) {
                    parent->setcurrent(taskCount() - 1);
                    parent->timer->setTime(0);
                    parent->currTaskLabel->setText("All tasks finished");
                } else {
                    if(!parent->wasStarted)
                        parent->timer->setTime(getPTasks().at(parent->getcurrent())->getDuration()*60);
                    parent->updateCurrentTaskLabel();
                }
            }
        }
    });

    QPushButton* upButton = new QPushButton("↑");
    QPushButton* downButton = new QPushButton("↓");

    upButton->setFixedSize(25, 25);
    downButton->setFixedSize(25, 25);

    QVBoxLayout* arrowLayout = new QVBoxLayout();
    arrowLayout->addWidget(upButton);
    arrowLayout->addWidget(downButton);
    arrowLayout->setSpacing(0);
    arrowLayout->setContentsMargins(0, 0, 0, 0);

    QWidget* arrowWidget = new QWidget();
    arrowWidget->setLayout(arrowLayout);
    arrowWidget->setFixedWidth(50);

    QObject::connect(upButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        int index = tasks.indexOf(task);

        if(parent->wasStarted == true) {
            if(index > 0  && (index - 1) > parent->getcurrent()) {
                reorderTasks(index, index - 1);
                if(index == parent->getcurrent() || index - 1 == parent->getcurrent())
                    parent->timer->setTime(getPTasks().at(parent->getcurrent())->getDuration()*60);
            }
        } else {
            if(index >= 0 && (index - 1) >= parent->getcurrent()) {
                reorderTasks(index, index - 1);
                if(index == parent->getcurrent() || index - 1 == parent->getcurrent())
                    parent->timer->setTime(getPTasks().at(parent->getcurrent())->getDuration()*60);
            }
        }
        refreshList(qobject_cast<QVBoxLayout*>(fieldWidget->parentWidget()->layout()));
    });

    QObject::connect(downButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        int index = tasks.indexOf(task);

        if(parent->wasStarted == true) {
            if(index < tasks.size() - 1 && index > parent->getcurrent()) {
                reorderTasks(index, index + 1);
                if(index == parent->getcurrent() || index + 1 == parent->getcurrent())
                    parent->timer->setTime(getPTasks().at(parent->getcurrent())->getDuration()*60);
            }
        } else {
            if(index < tasks.size() - 1 && index >= parent->getcurrent()) {
                reorderTasks(index, index + 1);
                if(index == parent->getcurrent() || index + 1 == parent->getcurrent())
                    parent->timer->setTime(getPTasks().at(parent->getcurrent())->getDuration()*60);
            }
        }
        refreshList(qobject_cast<QVBoxLayout*>(fieldWidget->parentWidget()->layout()));
    });

    if(task->getStatus())
        task->lineEdit->setStyleSheet( "background-color: #a7a7a7; border: 1px solid #4c4c4c; "
        "border-radius: 5px; padding: 5px; color: black; text-decoration: line-through;");

    inputLayout->addWidget(task->lineEdit);
    inputLayout->addWidget(durationBox);
    inputLayout->addSpacing(10);
    inputLayout->addWidget(deleteButton);
    inputLayout->addSpacing(10);
    inputLayout->addWidget(arrowWidget);


    if(settings->getTheme() == "Light") {
        deleteButton->setStyleSheet("QPushButton { background-color: #ffa726; color: black; border-radius: 5px; } QPushButton:hover { background-color: #fb8c00; color: white; }");
        upButton->setStyleSheet("QPushButton { background-color: #ffe0b2; color: black; border-radius: 5px; border: 1px solid #4c4c4c;}");
        downButton->setStyleSheet("QPushButton { background-color: #ffe0b2; color: black; border-radius: 5px; border: 1px solid #4c4c4c;}");
    }
    else if(settings->getTheme() == "Dark") {
        deleteButton->setStyleSheet("QPushButton { background-color: #dd2c00; color: white; border-radius: 5px; } QPushButton:hover { background-color: #8b0000; color: white; }");
        upButton->setStyleSheet("QPushButton { background-color: #7c7c7c; color: white; border-radius: 5px; }");
        downButton->setStyleSheet("QPushButton { background-color: #7c7c7c; color: white; border-radius: 5px; }");
    }

    return fieldWidget;
}

void PomodoroList::refreshList(QVBoxLayout* layout) {
    QLayoutItem* child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for(PomodoroTask* task : tasks)
        layout->addWidget(createTaskWidget(task), 0, Qt::AlignLeft);
}

void PomodoroList::databaseInit() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "PomodoroConnection");
    db.setDatabaseName("pomodoroTasks.db");

    if(!db.open())
        return;

    QSqlQuery query(db);
    QString createTable = R"(
        CREATE TABLE IF NOT EXISTS pomodoroTasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            isCompleted INTEGER NOT NULL,
            duration INTEGER NOT NULL
        )
    )";

    if(!query.exec(createTable))
        return;
}

void PomodoroList::saveToDatabase() {
    QSqlDatabase db = QSqlDatabase::database("PomodoroConnection");

    if(!db.isOpen())
        return;

    QSqlQuery query(db);

    if(!query.exec("DELETE FROM pomodoroTasks"))
        return;

    query.prepare("INSERT INTO pomodoroTasks (name, isCompleted, duration) VALUES (:name, :isCompleted, :duration)");

    for(PomodoroTask* task : tasks) {
        query.bindValue(":name", task->getName());
        query.bindValue(":isCompleted", task->getStatus() ? 1 : 0);
        query.bindValue(":duration", task->getDuration());

        if(!query.exec())
            return;
    }
}
void PomodoroList::loadFromDatabase() {
    QSqlDatabase db = QSqlDatabase::database("PomodoroConnection");

    if(!db.isOpen())
        return;

    QSqlQuery query(db);
    if(!query.exec("SELECT name, isCompleted, duration FROM pomodoroTasks"))
        return;

    qDeleteAll(tasks);
    tasks.clear();

    while(query.next()) {
        QString name = query.value(0).toString();
        bool isCompleted = query.value(1).toInt() == 1;
        int duration = query.value(2).toInt();

        PomodoroTask* newTask = new PomodoroTask(name, duration);
        if(isCompleted)
            newTask->setStatus(true);

        tasks.append(newTask);
    }
}
