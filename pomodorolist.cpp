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
    if(tasks.size() == parent->tasksFinished) {
        parent->timer->setTime(pt->getDuration());
        parent->setcurrent(parent->tasksFinished);
    }
    tasks.append(pt);

    if(parent != nullptr)
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

    if(parent != nullptr)
        parent->updateCurrentTaskLabel();
}
void PomodoroList::editTaskDuration(Task* task, int newDuration) {
    PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);

    pt->editDuration(newDuration);
    parent->updateCurrentTaskLabel();
}

QWidget* PomodoroList::createTaskWidget(PomodoroTask* task) {
    QWidget* fieldWidget = new QWidget();
    QHBoxLayout* inputLayout = new QHBoxLayout(fieldWidget);
    inputLayout->setContentsMargins(10, 10, 10, 10);
    inputLayout->setSpacing(0);

    task->lineEdit = new QLineEdit(task->getName());
    task->lineEdit->setFixedSize(300, 50);
    task->lineEdit->setPlaceholderText("Enter task name");

    QSpinBox* durationBox = new QSpinBox();
    durationBox->setFixedHeight(50);
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

    QObject::connect(task->lineEdit, &QLineEdit::textChanged, [this, task](const QString& newName) {
        this->editTaskName(task, newName);
    });

    QObject::connect(durationBox, &QSpinBox::valueChanged, [this, task, durationBox](int newDuration) {
        PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);
        int index = tasks.indexOf(pt);

        if(index > parent->getcurrent())
            this->editTaskDuration(task, newDuration);
        else {
            durationBox->blockSignals(true);
            durationBox->setValue(pt->getDuration());
            durationBox->blockSignals(false);
        }
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
        PomodoroTask* pt = dynamic_cast<PomodoroTask*>(task);
        int index = tasks.indexOf(pt);

        if(index > parent->getcurrent()) {
            this->removeTask(task);
            fieldWidget->deleteLater();
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
        if(index > 0 && index > parent->getcurrent() && (index - 1) > parent->getcurrent()) {
            reorderTasks(index, index - 1);
            refreshList(qobject_cast<QVBoxLayout*>(fieldWidget->parentWidget()->layout()));
        }
    });

    QObject::connect(downButton, &QPushButton::clicked, [this, task, fieldWidget]() {
        int index = tasks.indexOf(task);
        if(index < tasks.size() - 1 && index > parent->getcurrent() && (index + 1) > parent->getcurrent()) {
            reorderTasks(index, index + 1);
            refreshList(qobject_cast<QVBoxLayout*>(fieldWidget->parentWidget()->layout()));
        }
    });

    if(task->getStatus())
        task->lineEdit->setStyleSheet(lineEditStyle + "text-decoration: line-through;");

    inputLayout->addWidget(task->lineEdit);
    inputLayout->addWidget(durationBox);
    inputLayout->addSpacing(10);
    inputLayout->addWidget(deleteButton);
    inputLayout->addSpacing(10);
    inputLayout->addWidget(arrowWidget);


    if(settings->getTheme() == "Light") {
        deleteButton->setStyleSheet("QPushButton { background-color: #ffa726; color: black; border-radius: 5px; }");

        upButton->setStyleSheet("QPushButton { background-color: #ffe0b2; color: black; border-radius: 5px; }");
        downButton->setStyleSheet("QPushButton { background-color: #ffe0b2; color: black; border-radius: 5px; }");
    }
    else if(settings->getTheme() == "Dark") {
        deleteButton->setStyleSheet("QPushButton { background-color: #dd2c00; color: white; border-radius: 5px; }");

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

void PomodoroList::saveToDatabase() {}
void PomodoroList::updateInDatabase(Task* task) {}
void PomodoroList::loadFromDatabase() {}
