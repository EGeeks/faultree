#include "login.h"
#include <QApplication>
#include <QDir>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir dir;
    dir.mkdir(QDir::currentPath() + "/database");

    MainWindow w;
    w.hide();

    return a.exec();
}
