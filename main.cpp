#include "init_db.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    init_db();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
