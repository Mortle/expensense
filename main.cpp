#include "databasecreator.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    DatabaseCreator db;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
