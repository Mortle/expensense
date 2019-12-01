#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userswidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(new UsersWidget());
}

MainWindow::~MainWindow()
{
    delete ui;
}
