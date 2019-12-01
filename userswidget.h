#ifndef USERSWIDGET_H
#define USERSWIDGET_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui{
class UsersWidget;
}

class UsersWidget : public QWidget {
    Q_OBJECT
public:
    explicit UsersWidget(QWidget *parent = nullptr);
    ~UsersWidget();

signals:

public slots:

private:
    Ui::UsersWidget *ui;
    QSqlDatabase database;
    QSqlQueryModel *model;
};

#endif // USERSWIDGET_H
