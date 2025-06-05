#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    qputenv("QT_LOGGING_RULES", "qt.multimedia.ffmpeg=false");

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/Icon.ico"));
    w.show();

    return a.exec();
}

