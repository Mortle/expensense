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
    DatabaseConnector(QLatin1String usersQuery, QLatin1String incomeQuery,
                      QLatin1String expenseQuery, QLatin1String operationsQuery);

    static QVariant createUser(const QString &username, const QString &password);
    static QVariant createCategory(const QString &name, int user_id, bool expense, bool income, const QString &description);
    static void updateCategory(int id, const QString &name, const QString &description);
    static void removeCategory(int id);
    static QVariant createOperation(int category_id, int value, int user_id, const QString &description);
    static void updateOperation(int id, int category_id, int value, const QString &description);
    static void removeOperation(int id);

    QSqlQueryModel* getIncomeModel();
    QSqlQueryModel* getExpenseModel();
    QSqlQueryModel* getUsersModel();
    QSqlQueryModel* getOperationsModel();
};

#endif // DATABASECONNECTOR_H
