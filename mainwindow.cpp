#include "mainwindow.h"
#include "databaseconnector.h"
#include "ui_mainwindow.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshData()
{
    // Updating models and tableViews

    auto incomeQuery = QStringLiteral("SELECT name, description FROM categories WHERE income = 1 AND user_id = %1").arg(currentUserId);
    auto expenseQuery = QStringLiteral("SELECT name, description FROM categories WHERE income = 0 AND user_id = %1").arg(currentUserId);
    auto usersQuery = QStringLiteral("SELECT * FROM users");
    auto operationsQuery = QStringLiteral("SELECT id, category, value, created_at, description FROM operations WHERE user_id = %1").arg(currentUserId);

    DatabaseConnector db(usersQuery, incomeQuery, expenseQuery, operationsQuery);

    auto operationsModel = db.getOperationsModel();
    operationsModel->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    operationsModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Category"));
    operationsModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Value, $"));
    operationsModel->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    operationsModel->setHeaderData(4, Qt::Horizontal, QObject::tr("Description"));

    auto incomeModel = db.getIncomeModel();
    incomeModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    incomeModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));

    auto expenseModel = db.getExpenseModel();
    expenseModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
    expenseModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));

    ui->operationsTableView->setModel(operationsModel);
    ui->expenseTableView->setModel(expenseModel);
    ui->incomeTableView->setModel(incomeModel);
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

    refreshData();
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

    double value = ui->newOperationValue->value();

    QString desc = ui->newOperationDesc->text();

    QString categoryName = ui->newOperationCategory->text();

    // Category existence check

    bool exists = false;
    QSqlQuery query;
    query.prepare("SELECT name FROM categories WHERE user_id = ?");
    query.addBindValue(currentUserId);
    query.exec();
    while(query.next()){
        if(categoryName == query.value(0).toString()){
            exists = true;
        }
    }
    if(exists == false){
        ui->statusbar->setStyleSheet("color: #ff0000");
        ui->statusbar->showMessage("Category with entered name does not exist. Please, try again.", 10000);
        ui->newOperationCategory->setText("");
        return;
    }

    DatabaseConnector::createOperation(categoryName, value, currentUserId, desc);
    ui->statusbar->setStyleSheet("color: #008000");
    ui->statusbar->showMessage("Created new operation successfully", 10000);

    // Clearing input fields

    ui->newOperationCategory->setText("");
    ui->newOperationValue->setValue(0);
    ui->newOperationDesc->setText("");

    refreshData();
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

    refreshData();
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

    refreshData();
}

void MainWindow::on_createExpCategoryPushButton_clicked()
{
    auto desc = ui->createECategoryDesc->toPlainText();
    auto name = ui->createECategoryName->text();

    if(name.isEmpty()){
        ui->statusbar->setStyleSheet("color: #ff0000");
        ui->statusbar->showMessage("Entered category name is not valid. Please, try again", 10000);
        return;
    }

    // Check if category with entered name already exists

    QSqlQuery query;
    query.prepare("SELECT name FROM categories WHERE user_id = ?");
    query.addBindValue(currentUserId);
    query.exec();
    while(query.next()){
        auto name_ = query.value(0).toString();
        if(name == name_){
            ui->statusbar->setStyleSheet("color: #ff0000");
            ui->statusbar->showMessage("Category with entered name already exists. Please, try again", 10000);
            return;
        }
    }

    DatabaseConnector::createCategory(name, currentUserId, true, false, desc);

    ui->statusbar->setStyleSheet("color: #008000");
    ui->statusbar->showMessage("Created new category successfully", 10000);

    // Clearing input fields

    ui->createECategoryName->setText("");
    ui->createECategoryDesc->setPlainText("");

    refreshData();
}

void MainWindow::on_removeExpCategoryPushButton_clicked()
{
    auto name = ui->removeECategoryName->text();

    QSqlQuery query;
    query.prepare("SELECT name FROM categories WHERE user_id = ? AND expense = ?");
    query.addBindValue(currentUserId);
    query.addBindValue(true);
    query.exec();
    bool found = false;
    while(query.next()){
        auto name_ = query.value(0).toString();
        if(name == name_){
            DatabaseConnector::removeCategory(name, currentUserId);
            found = true;
            break;
        }
    }

    if(found == false){
        ui->statusbar->setStyleSheet("color: #ff0000");
        ui->statusbar->showMessage("Category with entered name does not exist. Please, try again", 10000);
        return;
    }

    ui->statusbar->setStyleSheet("color: #008000");
    ui->statusbar->showMessage("Deleted category successfully", 10000);

    // Clearing input fields

    ui->removeECategoryName->setText("");

    refreshData();
}

void MainWindow::on_createIncCategoryPushButton_clicked()
{
    auto desc = ui->createICategoryDesc->toPlainText();
    auto name = ui->createICategoryName->text();

    if(name.isEmpty()){
        ui->statusbar->setStyleSheet("color: #ff0000");
        ui->statusbar->showMessage("Entered category name is not valid. Please, try again", 10000);
        return;
    }

    // Check if category with entered name already exists

    QSqlQuery query;
    query.prepare("SELECT name FROM categories WHERE user_id = ?");
    query.addBindValue(currentUserId);
    query.exec();
    while(query.next()){
        auto name_ = query.value(0).toString();
        if(name == name_){
            ui->statusbar->setStyleSheet("color: #ff0000");
            ui->statusbar->showMessage("Category with entered name already exists. Please, try again", 10000);
            return;
        }
    }

    DatabaseConnector::createCategory(name, currentUserId, false, true, desc);

    ui->statusbar->setStyleSheet("color: #008000");
    ui->statusbar->showMessage("Created new category successfully", 10000);

    // Clearing input fields

    ui->createICategoryName->setText("");
    ui->createICategoryDesc->setPlainText("");

    refreshData();
}

void MainWindow::on_removeIncCategoryPushButton_clicked()
{
    auto name = ui->removeICategoryName->text();

    QSqlQuery query;
    query.prepare("SELECT name FROM categories WHERE user_id = ? AND income = ?");
    query.addBindValue(currentUserId);
    query.addBindValue(true);
    query.exec();
    bool found = false;
    while(query.next()){
        auto name_ = query.value(0).toString();
        if(name == name_){
            DatabaseConnector::removeCategory(name, currentUserId);
            found = true;
            break;
        }
    }

    if(found == false){
        ui->statusbar->setStyleSheet("color: #ff0000");
        ui->statusbar->showMessage("Category with entered name does not exist. Please, try again", 10000);
        return;
    }

    ui->statusbar->setStyleSheet("color: #008000");
    ui->statusbar->showMessage("Deleted category successfully", 10000);

    // Clearing input fields

    ui->removeICategoryName->setText("");

    refreshData();
}
