#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto incomeModel = new QSqlQueryModel();
    incomeModel->setQuery("SELECT name, description FROM categories WHERE income = 1");
    ui->incomeTableView->setModel(incomeModel);

    auto expenseModel = new QSqlQueryModel();
    expenseModel->setQuery("SELECT name, description FROM categories WHERE income = 0");
    ui->expenseTableView->setModel(expenseModel);

    auto operationsModel = new QSqlQueryModel();
    operationsModel->setQuery("SELECT * FROM operations");
    ui->operationsTableView->setModel(operationsModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginPushButton_clicked()
{
    if(1/* loggedIn() */) {
        ui->stackedWidget->setCurrentIndex(0);
    } else {

    }
}

void MainWindow::on_logoutPushButton_clicked()
{
    if(1/* loggedIn() */) {
        ui->stackedWidget->setCurrentIndex(1);
    } else {

    }
}
