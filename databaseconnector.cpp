#include "databaseconnector.h"

DatabaseConnector::DatabaseConnector(QLatin1String usersQuery, QLatin1String incomeQuery,
                                     QLatin1String expenseQuery, QLatin1String operationsQuery) {
    usersModel = new QSqlQueryModel;
    usersModel->setQuery(usersQuery);
    incomeModel = new QSqlQueryModel;
    incomeModel->setQuery(incomeQuery);
    expenseModel = new QSqlQueryModel;
    expenseModel->setQuery(expenseQuery);
    operationsModel = new QSqlQueryModel;
    operationsModel->setQuery(operationsQuery);
}

QVariant DatabaseConnector::createUser(const QString &username, const QString &password) {
    const auto sql = QLatin1String(R"(
        insert into users(username, password, created_at) values(?, ?, ?)
        )");
    QSqlQuery q;
    q.prepare(sql);
    q.addBindValue(username);
    q.addBindValue(password);
    q.addBindValue(QDateTime::currentDateTime().toString());
    q.exec();
    return q.lastInsertId();
}

QVariant DatabaseConnector::createCategory(const QString &name, int user_id, bool expense, bool income, const QString &description) {
    //TODO: reject if (name, expense, income) already exists
    //TODO: desc. length validation
    const auto sql = QLatin1String(R"(
        insert into categories(name, user_id, expense, income, description, created_at) values(?, ?, ?, ?, ?, ?)
        )");
    QSqlQuery q;
    q.prepare(sql);
    q.addBindValue(name);
    q.addBindValue(user_id);
    q.addBindValue(expense);
    q.addBindValue(income);
    q.addBindValue(description);
    q.addBindValue(QDateTime::currentDateTime().toString());
    q.exec();
    return q.lastInsertId();
}

void DatabaseConnector::updateCategory(int id, const QString &name, const QString &description) {
    //TODO: reject if (name, expense, income) already exists
    //TODO: desc. length validation
    QSqlQuery q;
    q.prepare("UPDATE categories SET name = ?, description = ? WHERE id = ?");
    q.addBindValue(name);
    q.addBindValue(description);
    q.addBindValue(id);
    q.exec();
}

void DatabaseConnector::removeCategory(int id) {
    //TODO: remove all operations with category_id === id
    //TODO: QMessageBox warning: all operations will be deleted
    QSqlQuery q;
    q.prepare("DELETE FROM categories WHERE id = ?");
    q.addBindValue(id);
    q.exec();
}

QVariant DatabaseConnector::createOperation(int category_id, int value, int user_id, const QString &description) {
    //TODO: category_id exists? validation
    //TODO: desc. length validation
    //TODO: value validation
    QSqlQuery q;
    q.prepare("insert into operations(category_id, user_id, value, description, created_at) values(?, ?, ?, ?, ?)");
    q.addBindValue(category_id);
    q.addBindValue(user_id);
    q.addBindValue(value);
    q.addBindValue(description);
    q.addBindValue(QDateTime::currentDateTime().toString());
    q.exec();
    return q.lastInsertId();
}

void DatabaseConnector::updateOperation(int id, int category_id, int value, const QString &description) {
    //TODO: new categody_id exists? validation
    QSqlQuery q;
    q.prepare("UPDATE operations SET category_id = ?, description= ?, value = ? WHERE id = ?");
    q.addBindValue(category_id);
    q.addBindValue(description);
    q.addBindValue(value);
    q.addBindValue(id);
    q.exec();
}

void DatabaseConnector::removeOperation(int id) {
    QSqlQuery q;
    q.prepare("DELETE FROM operations WHERE id = ?");
    q.addBindValue(id);
    q.exec();
}

QSqlQueryModel* DatabaseConnector::getIncomeModel() {
    return incomeModel;
}

QSqlQueryModel* DatabaseConnector::getExpenseModel() {
    return expenseModel;
}

QSqlQueryModel* DatabaseConnector::getUsersModel() {
    return usersModel;
}

QSqlQueryModel* DatabaseConnector::getOperationsModel() {
    return operationsModel;
}

