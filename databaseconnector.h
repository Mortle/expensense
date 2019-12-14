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
    DatabaseConnector(QString usersQuery, QString incomeQuery,
                      QString expenseQuery, QString operationsQuery);

    static QVariant createUser(const QString &username, const QString &password);
    static QVariant createCategory(const QString &name, int user_id, bool expense, bool income, const QString &description);
    static void updateCategory(int id, const QString &name, const QString &description);
    static void removeCategory(int id);
    static QVariant createOperation(const QString &categoryName, double value, int user_id, const QString &description);
    static void updateOperation(int id, double value, const QString &description);
    static void removeOperation(int id);

    QSqlQueryModel* getIncomeModel();
    QSqlQueryModel* getExpenseModel();
    QSqlQueryModel* getUsersModel();
    QSqlQueryModel* getOperationsModel();

    static bool validateUser(const QString &username, const QString &password);

    static int signIn(const QString &username, const QString &password);
};

#endif // DATABASECONNECTOR_H
