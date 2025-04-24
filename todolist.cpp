#include "todolist.h"
#include "task.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QTimer>
#include <QPushButton>
#include <QApplication>

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

void ToDoList::reorderTasks(QVector<Task*> newOrder) {
    tasks = newOrder;
}

void ToDoList::saveToDatabase() {}
void ToDoList::updateInDatabase(Task* task) {}
void ToDoList::loadFromDatabase() {}

QWidget* ToDoList::createTaskWidget(Task* task) {
    QWidget* fieldWidget = new QWidget();
    QHBoxLayout* inputLayout = new QHBoxLayout(fieldWidget);

    QLineEdit* lineEdit = new QLineEdit(task->getName());
    lineEdit->setFixedSize(400, 60);
    lineEdit->setStyleSheet("QLineEdit { background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 5px; color: black; }");

    QObject::connect(lineEdit, &QLineEdit::textChanged, [task](const QString& newName) {
        task->editName(newName);
    });

    QCheckBox* checkBox = new QCheckBox("✔");
    checkBox->setChecked(task->getStatus());

    if(task->getStatus())
        lineEdit->setStyleSheet("QLineEdit { background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 5px; color: black; text-decoration: line-through; }");

    QObject::connect(checkBox, &QCheckBox::toggled, [this, task, lineEdit](bool checked) {
        task->editStatus();
        if (checked)
            lineEdit->setStyleSheet("QLineEdit { background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 5px; color: black; text-decoration: line-through; }");
        else
            lineEdit->setStyleSheet("QLineEdit { background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 5px; color: black; }");

    });

    QPushButton* deleteButton = new QPushButton("🗑");
    deleteButton->setFixedSize(40, 40);
    deleteButton->setStyleSheet("QPushButton { background-color: #e57373; color: white; border-radius: 5px; }");

    QObject::connect(deleteButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        removeTask(task);
        fieldWidget->deleteLater();
    });

    inputLayout->addWidget(lineEdit);
    inputLayout->addWidget(checkBox);
    inputLayout->addWidget(deleteButton);


    return fieldWidget;
}

void ToDoList::refreshListIn(QVBoxLayout* layout) {
    QLayoutItem* child;
    while((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for(Task* task : tasks)
        layout->addWidget(createTaskWidget(task), 0, Qt::AlignHCenter);
}
