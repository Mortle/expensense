#include "ui_userswidget.h"

UsersWidget::UsersWidget(QWidget *parent) : QWidget(parent)
{
    ui->setupUi(this);

    model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM users");

    ui->tableView->setModel(model);
}

UsersWidget::~UsersWidget(){
    delete ui;
}
