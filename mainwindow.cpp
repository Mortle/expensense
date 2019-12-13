#include "mainwindow.h"
#include "databaseconnector.h"
#include "ui_mainwindow.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Adding model-views

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

void MainWindow::on_createOperationPushButton_clicked()
{
    bool expense = false;
    bool income = false;

    if (ui->expenseOperationRadioButton->isChecked()){
        expense = true;
    }
    if(ui->incomeOperationRadioButton->isChecked()){
        income = true;
    }
    if(expense == false && income == false){
        ui->statusbar->setStyleSheet("color: #ff0000");
        ui->statusbar->showMessage("Please, select operation type (income | expense).", 10000);
        return;
    }

    int value = ui->newOperationValue->value();

    QString desc = ui->newOperationDesc->text();

    // Getting category ID from database

    QString categoryName = ui->newOperationCategory->text();
    QSqlQuery query;
    query.prepare("SELECT id FROM categories WHERE name = ? AND user_id = ? AND expense = ? AND income = ?");
    query.addBindValue(categoryName);
    query.addBindValue(currentUserId);
    query.addBindValue(expense);
    query.addBindValue(income);
    query.exec();
    int categoryId = 0;
    while (query.next()){
        categoryId = query.value(0).toInt();
    }

    if(categoryId == 0){
        ui->statusbar->setStyleSheet("color: #ff0000");
        ui->statusbar->showMessage("Category with entered name does not exist. Please, try again.", 10000);
        ui->newOperationCategory->setText("");
        return;
    }

    DatabaseConnector::createOperation(categoryId, value, currentUserId, desc);
    ui->statusbar->setStyleSheet("color: #008000");
    ui->statusbar->showMessage("Created new operation successfully", 10000);

    // Clearing input fields

    ui->newOperationCategory->setText("");
    ui->newOperationValue->setValue(0);
    ui->newOperationDesc->setText("");
}

void MainWindow::on_updateOperationPushButton_clicked()
{
    auto id = ui->updOperationID->value();
    auto desc = ui->updOperationDesc->text();
    auto value = ui->updOperationValue->value();

    // Validating input

    QSqlQuery query;
    query.prepare("SELECT * FROM operations WHERE id = ? AND user_id = ?");
    query.addBindValue(id);
    query.addBindValue(currentUserId);
    query.exec();
    if(query.next()){
        DatabaseConnector::updateOperation(id, value, desc);

        ui->statusbar->setStyleSheet("color: #008000");
        ui->statusbar->showMessage("Updated selected operation successfully", 10000);

        // Clearing input fields

        ui->updOperationValue->setValue(0);
        ui->updOperationDesc->setText("");
        ui->updOperationID->setValue(0);
    } else {
        ui->statusbar->setStyleSheet("color: #ff0000");
        ui->statusbar->showMessage("Operation with entered ID does not exist. Please, try again", 10000);
    }
}

void MainWindow::on_deleteOperationPushButton_clicked()
{
    auto id = ui->deleteOperationID->value();

    QSqlQuery query;
    query.prepare("SELECT * FROM operations WHERE id = ? AND user_id = ?");
    query.addBindValue(id);
    query.addBindValue(currentUserId);
    query.exec();
    if (query.next()){
        DatabaseConnector::removeOperation(id);

        ui->statusbar->setStyleSheet("color: #008000");
        ui->statusbar->showMessage("Deleted selected operation successfully", 10000);

        // Clearing input fields

        ui->deleteOperationID->setValue(0);
    } else {
        ui->statusbar->setStyleSheet("color: #ff0000");
        ui->statusbar->showMessage("Operation with entered ID does not exist. Please, try again", 10000);
    }
}
