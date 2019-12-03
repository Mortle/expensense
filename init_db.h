#ifndef INIT_DB_H
#define INIT_DB_H

#include <QtSql>
#include <CRUD.h>

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

    create_user(QLatin1String("dima.osipov2000@mail.ru"), QLatin1String("Dmitry Osipov"),
             QLatin1String("AMz6J34Mg&zJ9@MC"));
    create_user(QLatin1String("3vinogradof@gmail.com"), QLatin1String("Alexander Vinogradov"),
             QLatin1String("boomer"));
    create_user(QLatin1String("duleba2018@gmail.com"), QLatin1String("Valery Duleba"),
             QLatin1String("e3LQ6T&Eh6kp-J&6"));

    create_category(QLatin1String("Other"), 0, true, false, QLatin1String(""));
    create_category(QLatin1String("Cafe"), 0, true, false, QLatin1String(""));
    create_category(QLatin1String("Rent"), 0, true, false, QLatin1String(""));
    create_category(QLatin1String("Food"), 0, true, false, QLatin1String(""));
    create_category(QLatin1String("Entertainment"), 0, true, false, QLatin1String(""));
    create_category(QLatin1String("Salary"), 0, false, true, QLatin1String(""));
    create_category(QLatin1String("Scholarship"), 0, false, true, QLatin1String(""));

    return QSqlError();
}
#endif // INIT_DB_H
