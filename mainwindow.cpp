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
    incomeModel->setQuery("SELECT name, description, created_at FROM categories WHERE income = 1");
    ui->incomeTableView->setModel(incomeModel);

    auto expenseModel = new QSqlQueryModel();
    expenseModel->setQuery("SELECT name, description, created_at FROM categories WHERE income = 0");
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
    if(1 /* !QString::compare(ui->loginPassword->text(), "gucci") */) {
        ui->stackedWidget->setCurrentIndex(0);
        // set_current_user(username);
    } else {
        // error in status bar
    }
}

void MainWindow::on_logoutPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_registerPushButton_clicked()
{
//    if(!QString::compare(ui->registerPassword->text(), ui->registerConfirmPassword->text())
//       && password_valid(ui->registerPassword->text()) // delete, this logic must be written in CRUD
//       && username_valid(ui->registerUsername->text())) {
//        if (create_user("remove email option later", ui->registerUsername->text(),
//                    ui->registerPassword->text())) {

//        } else {

//        }
//        // account was created, please sign in
//    } else {
//        // entered data is not valid, try again
//    }
}
