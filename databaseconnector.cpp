#include "databaseconnector.h"

DatabaseConnector::DatabaseConnector(QString usersQuery, QString incomeQuery,
                                     QString expenseQuery, QString operationsQuery) {
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
    auto dateTime = QDateTime::currentDateTime();
    QString dateTimeUnlocalized = QLocale{QLocale::English}.toString(dateTime, "yyyy-MM-dd");
    q.addBindValue(dateTimeUnlocalized);
    q.exec();
    return q.lastInsertId();
}

QVariant DatabaseConnector::createCategory(const QString &name, int user_id, bool expense, bool income, const QString &description) {
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
    auto dateTime = QDateTime::currentDateTime();
    QString dateTimeUnlocalized = QLocale{QLocale::English}.toString(dateTime, "yyyy-MM-dd");
    q.addBindValue(dateTimeUnlocalized);
    q.exec();
    return q.lastInsertId();
}

void DatabaseConnector::updateCategory(int id, const QString &name, const QString &description) {
    QSqlQuery q;
    q.prepare("UPDATE categories SET name = ?, description = ? WHERE id = ?");
    q.addBindValue(name);
    q.addBindValue(description);
    q.addBindValue(id);
    q.exec();
}

void DatabaseConnector::removeCategory(int id) {
    QSqlQuery q;
    q.prepare("DELETE FROM categories WHERE id = ?");
    q.addBindValue(id);
    q.exec();
}

QVariant DatabaseConnector::createOperation(const QString &categoryName, double value, int user_id, const QString &description) {
    QSqlQuery q;
    q.prepare("insert into operations(category, user_id, value, description, created_at) values(?, ?, ?, ?, ?)");
    q.addBindValue(categoryName);
    q.addBindValue(user_id);
    q.addBindValue(value);
    q.addBindValue(description);
    auto dateTime = QDateTime::currentDateTime();
    QString dateTimeUnlocalized = QLocale{QLocale::English}.toString(dateTime, "yyyy-MM-dd");
    q.addBindValue(dateTimeUnlocalized);
    q.exec();
    return q.lastInsertId();
}

void DatabaseConnector::updateOperation(int id, double value, const QString &description) {
    QSqlQuery q;
    q.prepare("UPDATE operations SET description= ?, value = ? WHERE id = ?");
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

bool DatabaseConnector::validateUser(const QString &username, const QString &password)
{
    // Avoid username duplication

    QSqlQuery query;
    query.exec("SELECT username FROM users");
    while(query.next()) {
        QString _username = query.value(0).toString();
        if (!QString::compare(username, _username))
            return false;
    }

    // Username & Password data validation

    if(username.length() < 16 && username.length() > 3 &&
       password.length() < 16 && password.length() > 3) {
        return true;
    } else {
        return false;
    }
}

int DatabaseConnector::signIn(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.exec("SELECT id, username, password FROM users");
    while(query.next()) {
        int _id = query.value(0).toInt();
        QString _username = query.value(1).toString();
        QString _password = query.value(2).toString();
        if (!QString::compare(username, _username) && !QString::compare(password, _password)) {
            return _id;
        }
    }
    return 0;
}
