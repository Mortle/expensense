#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QtSql>
#include <QSqlQueryModel>

class DatabaseConnector
{
private:
    QSqlQueryModel *usersModel;
    QSqlQueryModel *incomeModel;
    QSqlQueryModel *expenseModel;
    QSqlQueryModel *operationsModel;

public:
    // Constructor designed to be invoked when seeding DB with sample data
    DatabaseConnector();

    // Constructor designed to be invoked when representing DB data
    DatabaseConnector(QLatin1String usersQuery, QLatin1String incomeQuery,
                      QLatin1String expenseQuery, QLatin1String operationsQuery);

    QVariant createUser(const QString &username, const QString &password);
    QVariant createCategory(const QString &name, int user_id, bool expense, bool income, const QString &description);
    void updateCategory(int id, const QString &name, const QString &description);
    void removeCategory(int id);
    QVariant createOperation(int category_id, int value, int user_id, const QString &description);
    void updateOperation(int id, int category_id, int value, const QString &description);
    void removeOperation(int id);

    QSqlQueryModel* getIncomeModel();
    QSqlQueryModel* getExpenseModel();
    QSqlQueryModel* getUsersModel();
    QSqlQueryModel* getOperationsModel();
};

#endif // DATABASECONNECTOR_H
