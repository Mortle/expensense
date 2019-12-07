#include "mainwindow.h"
#include "databaseconnector.h"
#include "ui_mainwindow.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto incomeQuery = QLatin1String("SELECT name, description, created_at FROM categories WHERE income = 1");
    auto expenseQuery = QLatin1String("SELECT name, description, created_at FROM categories WHERE income = 0");
    auto usersQuery = QLatin1String("SELECT * FROM users");
    auto operationsQuery = QLatin1String("SELECT * FROM operations");

    DatabaseConnector db(usersQuery, incomeQuery, expenseQuery, operationsQuery);

    ui->incomeTableView->setModel(db.getIncomeModel());
    ui->expenseTableView->setModel(db.getExpenseModel());
    ui->operationsTableView->setModel(db.getOperationsModel());
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
