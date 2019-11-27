#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectDB()
{
    // Connecting to SQLite Database

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("expensense_development.db");

    if(database.open()) {
        QMessageBox::information(this, "Success", "DB is open");
    } else {
        QMessageBox::critical(this, "Database Error", database.lastError().text());
    }

}
