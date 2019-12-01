#include "ui_userswidget.h"

UsersWidget::UsersWidget(QWidget *parent) : QWidget(parent)
{
    ui->setupUi(this);

//    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("development.db");

    model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM users");

    ui->tableView->setModel(model);
}

UsersWidget::~UsersWidget(){
    database.close();
    delete ui;
}
