#ifndef INIT_DB_H
#define INIT_DB_H

#include <QtSql>

QVariant add_user(QSqlQuery &q, const QString &email, const QString &username,
                  const QString &password) {
    q.addBindValue(email);
    q.addBindValue(username);
    q.addBindValue(password);
    q.addBindValue(QDateTime::currentDateTime().toString());
    q.exec();
    return q.lastInsertId();
}

QVariant add_category(QSqlQuery &q, const QString &name, int user_id,
                      bool expense, bool income, const QString &description) {
    q.addBindValue(name);
    q.addBindValue(user_id);
    q.addBindValue(expense);
    q.addBindValue(income);
    q.addBindValue(description);
    q.addBindValue(QDateTime::currentDateTime().toString());
    q.exec();
    return q.lastInsertId();
}

QVariant add_operation(QSqlQuery &q, int category_id, int value,
                       int user_id, const QString &description) {
    q.addBindValue(category_id);
    q.addBindValue(user_id);
    q.addBindValue(value);
    q.addBindValue(description);
    q.addBindValue(QDateTime::currentDateTime().toString());
    q.exec();
    return q.lastInsertId();
}

const auto USERS_SQL = QLatin1String(R"(
    create table users(id integer primary key, email varchar,
                        username varchar, password varchar, created_at varchar)
    )");

const auto OPERATIONS_SQL = QLatin1String(R"(
    create table operations(id integer primary key, category_id integer, user_id integer,
                            value int, description varchar, created_at varchar)
    )");

const auto CATEGORIES_SQL = QLatin1String(R"(
    create table categories(id integer primary key, name varchar, user_id integer,
                            expense boolean, income boolean, description varchar, created_at varchar)
    )");

const auto INSERT_USER_SQL = QLatin1String(R"(
    insert into users(email, username, password, created_at) values(?, ?, ?, ?)
    )");

const auto INSERT_OPERATION_SQL = QLatin1String(R"(
    insert into operations(category_id, user_id, value, description, created_at) values(?, ?, ?, ?, ?)
    )");

const auto INSERT_CATEGORY_SQL = QLatin1String(R"(
    insert into categories(name, user_id, expense, income, description, created_at) values(?, ?, ?, ?, ?, ?)
    )");

QSqlError init_db() {
    // Initializing SQLite database

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("development.db");

    if(!db.open())
        return db.lastError();

    // Checking if nessessary tables already exist

    QStringList tables = db.tables();
    if (tables.contains("users", Qt::CaseInsensitive)
        && tables.contains("categories", Qt::CaseInsensitive)
        && tables.contains("operations", Qt::CaseInsensitive))
        return QSqlError();

    // Creating tables

    QSqlQuery q;
    if (!q.exec(USERS_SQL))
        return q.lastError();
    if (!q.exec(OPERATIONS_SQL))
        return q.lastError();
    if (!q.exec(CATEGORIES_SQL))
        return q.lastError();

    // Seeding db with sample data

    if (!q.prepare(INSERT_USER_SQL))
        return q.lastError();
    add_user(q, QLatin1String("dima.osipov2000@mail.ru"), QLatin1String("Dmitry Osipov"),
             QLatin1String("AMz6J34Mg&zJ9@MC"));
    add_user(q, QLatin1String("3vinogradof@gmail.com"), QLatin1String("Alexander Vinogradov"),
             QLatin1String("boomer"));
    add_user(q, QLatin1String("duleba2018@gmail.com"), QLatin1String("Valery Duleba"),
             QLatin1String("e3LQ6T&Eh6kp-J&6"));

    if (!q.prepare(INSERT_CATEGORY_SQL))
        return q.lastError();
    add_category(q, QLatin1String("Other"), 0, true, false, QLatin1String(""));
    add_category(q, QLatin1String("Cafe"), 0, true, false, QLatin1String(""));
    add_category(q, QLatin1String("Rent"), 0, true, false, QLatin1String(""));
    add_category(q, QLatin1String("Food"), 0, true, false, QLatin1String(""));
    add_category(q, QLatin1String("Entertainment"), 0, true, false, QLatin1String(""));
    add_category(q, QLatin1String("Salary"), 0, false, true, QLatin1String(""));
    add_category(q, QLatin1String("Scholarship"), 0, false, true, QLatin1String(""));


    if (!q.prepare(INSERT_OPERATION_SQL))
        return q.lastError();

    return QSqlError();
}
#endif // INIT_DB_H
