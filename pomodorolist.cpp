#include "pomodorolist.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QPushButton>

void PomodoroList::addTask(Task* task) {
    PomodoroTask* PomoTask = dynamic_cast<PomodoroTask*>(task);
    tasks.append(PomoTask);
}
void PomodoroList::removeTask(Task* task) {
    PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);
    tasks.removeOne(pt);
}
void PomodoroList::editTaskName(Task* task, QString newName) {
    task->editName(newName);
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
}

void PomodoroList::saveToDatabase() {}
void PomodoroList::updateInDatabase(Task* task) {}
void PomodoroList::loadFromDatabase() {}
void PomodoroList::editTaskDuration(Task* task, int newDuration) {
    PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);
    pt->editDuration(newDuration);
}

QWidget* PomodoroList::createTaskWidget(PomodoroTask* task) {
    QWidget* fieldWidget = new QWidget();
    QHBoxLayout* inputLayout = new QHBoxLayout(fieldWidget);

    QLineEdit* lineEdit = new QLineEdit(task->getName());
    lineEdit->setFixedSize(300, 50);
    lineEdit->setStyleSheet("QLineEdit { background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 5px; color: black; }");

    QSpinBox* durationBox = new QSpinBox();
    durationBox->setMinimum(1);
    durationBox->setMaximum(180);
    durationBox->setValue(task->getDuration());
    durationBox->setSuffix(" min");

    /*
    QCheckBox* checkBox = new QCheckBox("Check");
    checkBox->setChecked(task->getStatus());

    if (task->getStatus()) {
        lineEdit->setStyleSheet("QLineEdit { background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 5px; color: black; text-decoration: line-through; }");
    }

    QObject::connect(checkBox, &QCheckBox::toggled, [this, task, lineEdit](bool checked) {
        task->editStatus();
        if (checked) {
            lineEdit->setStyleSheet("QLineEdit { background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 5px; color: black; text-decoration: line-through; }");
        } else {
            lineEdit->setStyleSheet("QLineEdit { background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 5px; color: black; }");
        }
    });
    */

    QObject::connect(lineEdit, &QLineEdit::textChanged, [task](const QString& newName) {
        task->editName(newName);
    });

    QObject::connect(durationBox, QOverload<int>::of(&QSpinBox::valueChanged), [this, task](int newDuration) {
        this->editTaskDuration(task, newDuration);
    });

    QPushButton* deleteButton = new QPushButton("🗑");
    deleteButton->setFixedSize(40, 40);
    deleteButton->setStyleSheet("QPushButton { background-color: #e57373; color: white; border-radius: 5px; }");

    QObject::connect(deleteButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        removeTask(task);
        fieldWidget->deleteLater();
    });

    QPushButton* upButton = new QPushButton("↑");
    QPushButton* downButton = new QPushButton("↓");

    upButton->setFixedSize(20, 20);
    downButton->setFixedSize(20, 20);

    upButton->setStyleSheet("QPushButton { background-color: #64b5f6; color: white; border-radius: 5px; }");
    downButton->setStyleSheet("QPushButton { background-color: #64b5f6; color: white; border-radius: 5px; }");

    QVBoxLayout* arrowLayout = new QVBoxLayout();
    arrowLayout->addWidget(upButton);
    arrowLayout->addWidget(downButton);
    arrowLayout->setSpacing(2);

    QWidget* arrowWidget = new QWidget();
    arrowWidget->setLayout(arrowLayout);
    arrowWidget->setFixedWidth(30);

    QObject::connect(upButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        int index = tasks.indexOf(task);
        if (index > 0) {
            reorderTasks(index, index - 1);
            refreshListIn(qobject_cast<QVBoxLayout*>(fieldWidget->parentWidget()->layout()));
        }
    });

    QObject::connect(downButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        int index = tasks.indexOf(task);
        if (index < tasks.size() - 1) {
            reorderTasks(index, index + 1);
            refreshListIn(qobject_cast<QVBoxLayout*>(fieldWidget->parentWidget()->layout()));
        }
    });

    inputLayout->addWidget(lineEdit);
    inputLayout->addWidget(durationBox);
    inputLayout->addWidget(deleteButton);
    //inputLayout->addWidget(checkBox);
    inputLayout->addWidget(arrowWidget);


    return fieldWidget;
}

void PomodoroList::refreshListIn(QVBoxLayout* layout) {
    QLayoutItem* child;
    while((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for(PomodoroTask* task : tasks)
        layout->addWidget(createTaskWidget(task), 0, Qt::AlignLeft);
}
