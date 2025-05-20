#include "todolist.h"
#include "task.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QTimer>
#include <QPushButton>
#include <QApplication>
#include <QDebug>

ToDoList::ToDoList() {
    tasks = QVector<Task*>();
}

void ToDoList::addTask(Task* task) {
    tasks.append(task);
}

void ToDoList::removeTask(Task* task) {
    tasks.removeOne(task);
}

void ToDoList::editTaskName(Task* task, QString newName) {
    task->editName(newName);
}

void ToDoList::editTaskStatus(Task* task) {
    task->editStatus();
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
}


void ToDoList::saveToDatabase() {}
void ToDoList::updateInDatabase(Task* task) {}
void ToDoList::loadFromDatabase() {}

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

    QObject::connect(lineEdit, &QLineEdit::textChanged, [task](const QString& newName) {
        task->editName(newName);
    });

    QCheckBox* checkBox = new QCheckBox(" ");
    checkBox->setChecked(task->getStatus());

    if(task->getStatus())
        lineEdit->setStyleSheet(lineEditStyle + "text-decoration: line-through;");

    QObject::connect(checkBox, &QCheckBox::toggled, [this, task, lineEdit, lineEditStyle](bool checked) {
        task->editStatus();
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
            "QCheckBox::indicator:checked { background-color: #ff9800; }"
            );

        deleteButton->setStyleSheet("QPushButton { background-color: #ffa726; color: black; border-radius: 5px; }");

        upButton->setStyleSheet("QPushButton { background-color: #ffe0b2; color: black; border-radius: 5px; }");
        downButton->setStyleSheet("QPushButton { background-color: #ffe0b2; color: black; border-radius: 5px; }");
    }
    else if(settings->getTheme() == "Dark") {
        checkBox->setStyleSheet(
            "QCheckBox::indicator { width: 16px; height: 16px; border-radius: 4px; background-color: #afafaf; }"
            "QCheckBox::indicator:checked { background-color: #4f4f4f; }"
            );

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
