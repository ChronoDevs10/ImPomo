#include "pomodorolist.h"
#include "extendedpomodoro.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>


void PomodoroList::addTask(Task* task) {
    PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);
    tasks.append(pt);
    parent->updateCurrentTaskLabel();
}
void PomodoroList::removeTask(Task* task) {
    PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);
    tasks.removeOne(pt);
    parent->updateCurrentTaskLabel();
}
void PomodoroList::editTaskName(Task* task, QString newName) {
    task->editName(newName);
    parent->updateCurrentTaskLabel();
}
void PomodoroList::editTaskStatus(Task* task) {
    task->editStatus();
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
    parent->updateCurrentTaskLabel();
}
void PomodoroList::editTaskDuration(Task* task, int newDuration) {
    PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);
    pt->editDuration(newDuration);
    parent->updateCurrentTaskLabel();
}

QWidget* PomodoroList::createTaskWidget(PomodoroTask* task) {
    QWidget* fieldWidget = new QWidget();
    //fieldWidget->setFixedHeight(100);

    QHBoxLayout* inputLayout = new QHBoxLayout(fieldWidget);
    inputLayout->setContentsMargins(10, 10, 10, 10);
    inputLayout->setSpacing(0);

    QLineEdit* lineEdit = new QLineEdit(task->getName());
    lineEdit->setFixedSize(300, 50);
    lineEdit->setStyleSheet(
        "QLineEdit {"
        "   font-size: 16px;"
        "   background-color: #f0f0f0;"
        "   border: 1px solid #ccc;"
        "   border-right: 1px solid #999;"
        "   border-top-left-radius: 5px;"
        "   border-bottom-left-radius: 5px;"
        "   padding: 5px 10px;"
        "   color: black;"
        "}"
    );

    QSpinBox* durationBox = new QSpinBox();
    durationBox->setFixedHeight(50);
    durationBox->setMinimum(1);
    durationBox->setMaximum(180);
    durationBox->setValue(task->getDuration());
    durationBox->setSuffix(" min");
    durationBox->setStyleSheet(
        "QSpinBox {"
        "   font-size: 16px;"
        "   background-color: #f0f0f0;"
        "   border: 1px solid #ccc;"
        "   border-left: none;"
        "   border-top-right-radius: 5px;"
        "   border-bottom-right-radius: 5px;"
        "   padding: 5px 10px;"
        "   color: black;"
        "}"
        "QSpinBox::up-button, QSpinBox::down-button { width: 0; height: 0; border: none; }"
        );

    QObject::connect(lineEdit, &QLineEdit::textChanged, [this, task](const QString& newName) {
        this->editTaskName(task, newName);
    });

    QObject::connect(durationBox, &QSpinBox::valueChanged, [this, task](int newDuration) {
        this->editTaskDuration(task, newDuration);
    });

    QPushButton* deleteButton = new QPushButton("🗑");
    deleteButton->setFixedSize(50, 50);
    deleteButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e57373;"
        "   color: white;"
        "   border-radius: 5px;"
        "   font-size: 18px;"
        "}"
    );

    QObject::connect(deleteButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        removeTask(task);
        fieldWidget->deleteLater();
    });

    QPushButton* upButton = new QPushButton("↑");
    QPushButton* downButton = new QPushButton("↓");

    upButton->setFixedSize(25, 25);
    downButton->setFixedSize(25, 25);

    QString arrowStyle =
        "QPushButton {"
        "   background-color: #64b5f6;"
        "   color: white;"
        "   border: 1px solid black;"
        "   border-radius: 5px;"
        "   height: 25px;"
        "}";

    upButton->setStyleSheet(arrowStyle);
    downButton->setStyleSheet(arrowStyle);

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
    inputLayout->addWidget(durationBox);
    inputLayout->addSpacing(10);
    inputLayout->addWidget(deleteButton);
    inputLayout->addSpacing(10);
    inputLayout->addWidget(arrowWidget);

    return fieldWidget;
}

void PomodoroList::refreshList(QVBoxLayout* layout) {
    QLayoutItem* child;
    while((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for(PomodoroTask* task : tasks)
        layout->addWidget(createTaskWidget(task), 0, Qt::AlignLeft);
}

void PomodoroList::saveToDatabase() {}
void PomodoroList::updateInDatabase(Task* task) {}
void PomodoroList::loadFromDatabase() {}
