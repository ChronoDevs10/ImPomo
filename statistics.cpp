#include "statistics.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QDialog>
#include <QDialogButtonBox>

Statistics::Statistics(){
    databaseInit();
}

void Statistics::databaseInit() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "StatisticsConnection");
    db.setDatabaseName("statistics.db");

    if(!db.open())
        return;

    QSqlQuery query(db);
    QString createTable = R"(
        CREATE TABLE IF NOT EXISTS dailyStats (
            date TEXT PRIMARY KEY,
            impomoTime INTEGER DEFAULT 0,
            pomodoroTime INTEGER DEFAULT 0,
            impomoTasks INTEGER DEFAULT 0
        )
    )";

    if(!query.exec(createTable))
        return;
}

void Statistics::addImpomoData(int timeSpent) {
    QSqlDatabase db = QSqlDatabase::database("StatisticsConnection");
    if(!db.isOpen())
        return;

    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QSqlQuery query(db);

    QString sql = R"(
        INSERT INTO dailyStats (date, impomoTime, impomoTasks)
        VALUES (:date, :time, 1)
        ON CONFLICT(date) DO UPDATE SET
            impomoTime = impomoTime + :time,
            impomoTasks = impomoTasks + 1
    )";

    query.prepare(sql);
    query.bindValue(":date", date);
    query.bindValue(":time", timeSpent);

    if(!query.exec())
        return;
}
void Statistics::addClassicPomodoroData(int timeSpent) {
    QSqlDatabase db = QSqlDatabase::database("StatisticsConnection");
    if(!db.isOpen())
        return;

    QString date = QDate::currentDate().toString("dd-MM-yyyy");
    QSqlQuery query(db);

    QString sql = R"(
        INSERT INTO dailyStats (date, pomodoroTime)
        VALUES (:date, :time)
        ON CONFLICT(date) DO UPDATE SET
            pomodoroTime = pomodoroTime + :time
    )";

    query.prepare(sql);
    query.bindValue(":date", date);
    query.bindValue(":time", timeSpent);

    if(!query.exec())
        return;
}

int Statistics::getDailyTimeImpomo(QString date) {
    QSqlDatabase db = QSqlDatabase::database("StatisticsConnection");
    if (!db.isOpen())
        return 0;

    QSqlQuery query(db);
    query.prepare("SELECT impomoTime FROM dailyStats WHERE date = :date");
    query.bindValue(":date", date);

    if (query.exec() && query.next())
        return query.value(0).toInt();

    return 0;
}

int Statistics::getDailyTimePomodoro(QString date) {
    QSqlDatabase db = QSqlDatabase::database("StatisticsConnection");
    if (!db.isOpen())
        return 0;

    QSqlQuery query(db);
    query.prepare("SELECT pomodoroTime FROM dailyStats WHERE date = :date");
    query.bindValue(":date", date);

    if (query.exec() && query.next())
        return query.value(0).toInt();

    return 0;
}
int Statistics::getDailyTasksNumber(QString date) {
    QSqlDatabase db = QSqlDatabase::database("StatisticsConnection");
    if (!db.isOpen())
        return 0;

    QSqlQuery query(db);
    query.prepare("SELECT impomoTasks FROM dailyStats WHERE date = :date");
    query.bindValue(":date", date);

    if (query.exec() && query.next())
        return query.value(0).toInt();

    return 0;
}

void Statistics::displayReport(const QDate& date) {
    QDialog dialog;
    dialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    dialog.setWindowTitle("Daily Statistics");
    dialog.setFixedSize(360, 220);
    QString style, label;

    if(appSettings->getTheme() == "Light") {
        style = "QDialog { background-color: #ffeccc; color: #000000; font-family: 'Segoe UI'; font-size: 14px; border: 5px solid #ffa726; border-radius: 8px; }\n"
                "QLabel { color: #000000; font-size: 16px; font-weight: bold; margin: 8px; }\n"
                "QDialogButtonBox QPushButton { background-color: #ffb74d; color: #000000; padding: 6px 14px; border-radius: 6px; font-weight: bold; }\n"
                "QDialogButtonBox QPushButton:hover { background-color: #ffa726; }\n"
                "QDialogButtonBox QPushButton:pressed { background-color: #fb8c00; }\n";
        label = "font-size: 20px; font-weight: bold; color: black; margin: 10px;";
    }
    else if(appSettings->getTheme() == "Dark") {
        style = "QDialog { background-color: #1a1a1a; color: #ffffff; font-family: 'Segoe UI'; font-size: 14px; border: 5px solid #444444; border-radius: 8px; }\n"
                "QLabel { color: #dddddd; font-size: 16px; font-weight: bold; margin: 8px; }\n"
                "QDialogButtonBox QPushButton { background-color: #5f5f5f; color: #ffffff; padding: 6px 14px; border-radius: 6px; font-weight: bold; }\n"
                "QDialogButtonBox QPushButton:hover { background-color: #7a7a7a; }\n"
                "QDialogButtonBox QPushButton:pressed { background-color: #9a9a9a; }\n";
        label = "font-size: 20px; font-weight: bold; color: white; margin: 10px;";
    }

    dialog.setStyleSheet(style);

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QString formattedDate = date.toString("dd-MM-yyyy");

    int impomoTime = getDailyTimeImpomo(formattedDate);
    int pomodoroTime = getDailyTimePomodoro(formattedDate);
    int taskCount = getDailyTasksNumber(formattedDate);

    QLabel* titleLabel = new QLabel(QString("Statistics for %1").arg(formattedDate));
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(label);
    layout->addWidget(titleLabel);

    QLabel* impomoLabel = new QLabel(QString("ImPomo work time: %1 min").arg(impomoTime));
    QLabel* pomodoroLabel = new QLabel(QString("Classic Pomodoro time: %1 min").arg(pomodoroTime));
    QLabel* tasksLabel = new QLabel(QString("Completed ImPomo tasks: %1").arg(taskCount));
    layout->addWidget(pomodoroLabel);
    layout->addWidget(impomoLabel);
    layout->addWidget(tasksLabel);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    layout->addWidget(buttonBox);

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);

    dialog.exec();
}
