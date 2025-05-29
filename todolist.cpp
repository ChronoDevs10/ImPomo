#include "todolist.h"
#include "task.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QTimer>
#include <QPushButton>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

ToDoList::ToDoList() {
    tasks = QVector<Task*>();
    databaseInit();
}

void ToDoList::addTask(Task* task) {
    tasks.append(task);
    saveToDatabase();
}

void ToDoList::removeTask(Task* task) {
    tasks.removeOne(task);
    saveToDatabase();
}

void ToDoList::editTaskName(Task* task, QString newName) {
    task->editName(newName);
    saveToDatabase();
}

void ToDoList::editTaskStatus(Task* task, bool status) {
    task->setStatus(status);
    saveToDatabase();
}

int ToDoList::taskCount() {
    return tasks.size();
}

QVector<Task*> ToDoList::getTasks() {
    return tasks;
}

void ToDoList::reorderTasks(int fromIndex, int toIndex) {
    if(fromIndex < 0 || toIndex < 0 || fromIndex >= tasks.size() || toIndex >= tasks.size())
        return;

    tasks.move(fromIndex, toIndex);
    saveToDatabase();
}

QWidget* ToDoList::createTaskWidget(Task* task) {
    QWidget* fieldWidget = new QWidget();
    QHBoxLayout* inputLayout = new QHBoxLayout(fieldWidget);

    QLineEdit* lineEdit = new QLineEdit(task->getName());
    lineEdit->setFixedSize(400, 60);
    lineEdit->setPlaceholderText("Enter task name");

    QString lineEditStyle;

    if(settings->getTheme() == "Light")
        lineEditStyle = "background-color: #ffe0b2; border: 1px solid #4c4c4c; border-radius: 5px; padding: 5px; color: black; ";
    else if(settings->getTheme() == "Dark")
        lineEditStyle = "background-color: #000000 ; border: 1px solid #5f5f5f; border-radius: 5px; padding: 5px; color: white; ";

    lineEdit->setStyleSheet(lineEditStyle);

    QObject::connect(lineEdit, &QLineEdit::textChanged, [this, task](const QString& newName) {
        editTaskName(task, newName);
    });

    QCheckBox* checkBox = new QCheckBox(" ");
    checkBox->setChecked(task->getStatus());

    if(task->getStatus())
        lineEdit->setStyleSheet(lineEditStyle + "text-decoration: line-through;");

    QObject::connect(checkBox, &QCheckBox::toggled, [this, task, lineEdit, lineEditStyle](bool checked) {
        editTaskStatus(task, checked);
        if(checked)
            lineEdit->setStyleSheet(lineEditStyle + "text-decoration: line-through;");
        else
            lineEdit->setStyleSheet(lineEditStyle);
    });

    QPushButton* deleteButton = new QPushButton("🗑");
    deleteButton->setFixedSize(40, 40);

    QObject::connect(deleteButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        removeTask(task);
        fieldWidget->deleteLater();
    });

    QPushButton* upButton = new QPushButton("↑");
    QPushButton* downButton = new QPushButton("↓");

    upButton->setFixedSize(20, 20);
    downButton->setFixedSize(20, 20);

    QVBoxLayout* arrowLayout = new QVBoxLayout();
    arrowLayout->addWidget(upButton);
    arrowLayout->addWidget(downButton);
    arrowLayout->setSpacing(2);

    QWidget* arrowWidget = new QWidget();
    arrowWidget->setLayout(arrowLayout);
    arrowWidget->setFixedWidth(30);

    QObject::connect(upButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        int index = tasks.indexOf(task);
        if(index > 0) {
            reorderTasks(index, index - 1);
            refreshList(qobject_cast<QVBoxLayout*>(fieldWidget->parentWidget()->layout()));
        }
    });

    QObject::connect(downButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        int index = tasks.indexOf(task);
        if(index < tasks.size() - 1) {
            reorderTasks(index, index + 1);
            refreshList(qobject_cast<QVBoxLayout*>(fieldWidget->parentWidget()->layout()));
        }
    });

    inputLayout->addWidget(lineEdit);
    inputLayout->addWidget(checkBox);
    inputLayout->addWidget(deleteButton);
    inputLayout->addWidget(arrowWidget);

    if(settings->getTheme() == "Light") {
        checkBox->setStyleSheet(
            "QCheckBox::indicator { width: 16px; height: 16px; border-radius: 4px; border: 1px solid gray; }"
            "QCheckBox::indicator:checked { background-color: #ff9800; }");

        deleteButton->setStyleSheet("QPushButton { background-color: #ffa726; color: black; border-radius: 5px; }");

        upButton->setStyleSheet("QPushButton { background-color: #ffe0b2; color: black; border-radius: 5px; border: 1px solid #4c4c4c;}");
        downButton->setStyleSheet("QPushButton { background-color: #ffe0b2; color: black; border-radius: 5px; border: 1px solid #4c4c4c;}");
    }
    else if(settings->getTheme() == "Dark") {
        checkBox->setStyleSheet(
            "QCheckBox::indicator { width: 16px; height: 16px; border-radius: 4px; background-color: #afafaf; }"
            "QCheckBox::indicator:checked { background-color: #4f4f4f; }");

        deleteButton->setStyleSheet("QPushButton { background-color: #dd2c00; color: white; border-radius: 5px; }");

        upButton->setStyleSheet("QPushButton { background-color: #7c7c7c; color: white; border-radius: 5px; }");
        downButton->setStyleSheet("QPushButton { background-color: #7c7c7c; color: white; border-radius: 5px; }");
    }
    return fieldWidget;
}

void ToDoList::refreshList(QVBoxLayout* layout) {
    QLayoutItem* child;
    while((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for(Task* task : tasks)
        layout->addWidget(createTaskWidget(task), 0, Qt::AlignHCenter);
}

void ToDoList::databaseInit() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "ToDoConnection");
    db.setDatabaseName("tasks.db");

    if(!db.open())
        return;

    QSqlQuery query(db);
    QString createTable = R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            isCompleted INTEGER NOT NULL
        )
    )";

    if(!query.exec(createTable))
        return;
}

void ToDoList::saveToDatabase() {
    QSqlDatabase db = QSqlDatabase::database("ToDoConnection");
    if(!db.isOpen())
        return;

    QSqlQuery query(db);

    if(!query.exec("DELETE FROM tasks"))
        return;

    query.prepare("INSERT INTO tasks (name, isCompleted) VALUES (:name, :isCompleted)");

    for(Task* task : tasks) {
        query.bindValue(":name", task->getName());
        query.bindValue(":isCompleted", task->getStatus() ? 1 : 0);

        if(!query.exec())
            return;
    }
}

void ToDoList::loadFromDatabase() {
    QSqlDatabase db = QSqlDatabase::database("ToDoConnection");

    if(!db.isOpen())
        return;

    QSqlQuery query(db);
    if (!query.exec("SELECT name, isCompleted FROM tasks"))
        return;

    qDeleteAll(tasks);
    tasks.clear();

    while(query.next()) {
        QString name = query.value(0).toString();
        bool isCompleted = query.value(1).toInt() == 1;

        Task* newTask = new Task(name);
        if(isCompleted)
            newTask->setStatus(true);

        tasks.append(newTask);
    }
}
