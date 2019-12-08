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
    currentUserId = DatabaseConnector::signIn(ui->loginUsername->text(), ui->loginPassword->text());
    if(currentUserId) {
        ui->stackedWidget->setCurrentIndex(0);

        ui->statusbar->setStyleSheet("color: #008000");
        ui->statusbar->showMessage("Logged in successfully", 10000);
    } else {
        ui->statusbar->setStyleSheet("color: #ff0000");
        ui->statusbar->showMessage("Entered data is not valid. Please, try again", 10000);
    }

    // Clear line edits text

    ui->loginUsername->setText("");
    ui->loginPassword->setText("");
}

void MainWindow::on_logoutPushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_registerPushButton_clicked()
{
    if(DatabaseConnector::validateUser(ui->registerUsername->text(), ui->registerPassword->text())
       && !QString::compare(ui->registerPassword->text(), ui->registerConfirmPassword->text())) {

        DatabaseConnector::createUser(ui->registerUsername->text(), ui->registerPassword->text());

        ui->statusbar->setStyleSheet("color: #008000");
        ui->statusbar->showMessage("Your account has been successfully created. Please, sign in to continue", 10000);
    } else {
        ui->statusbar->setStyleSheet("color: #ff0000");
        ui->statusbar->showMessage("Entered data is not valid or entered username already exists. Please, try again", 10000);
    }

    // Clear line edits text

    ui->registerUsername->setText("");
    ui->registerPassword->setText("");
    ui->registerConfirmPassword->setText("");
}
