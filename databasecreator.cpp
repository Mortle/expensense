#include "databasecreator.h"
#include "databaseconnector.cpp"

DatabaseCreator::DatabaseCreator()
{
    createUsersTableSql = QLatin1String(R"(
        create table users(id integer primary key, username varchar, password varchar, created_at varchar)
        )");

    createOperationsTableSql = QLatin1String(R"(
        create table operations(id integer primary key, category varchar, user_id integer,
                                value float, description varchar, created_at varchar)
        )");

    createCategoriesTableSql = QLatin1String(R"(
        create table categories(id integer primary key, name varchar, user_id integer,
                                expense boolean, income boolean, description varchar, created_at varchar)
        )");

    initializeDatabase("development.db");
}

QSqlError DatabaseCreator::initializeDatabase(QString dbName) {
    // Initializing SQLite database

    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

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
    if (!q.exec(createUsersTableSql))
        return q.lastError();
    if (!q.exec(createOperationsTableSql))
        return q.lastError();
    if (!q.exec(createCategoriesTableSql))
        return q.lastError();

    // Seeding db with sample data

    DatabaseConnector::createUser(QLatin1String("test"), QLatin1String("test"));

    DatabaseConnector::createCategory(QLatin1String("Other"), 1, true, false, QLatin1String(""));
    DatabaseConnector::createCategory(QLatin1String("Cafe"), 1, true, false, QLatin1String(""));
    DatabaseConnector::createCategory(QLatin1String("Rent"), 1, true, false, QLatin1String(""));
    DatabaseConnector::createCategory(QLatin1String("Food"), 1, true, false, QLatin1String(""));
    DatabaseConnector::createCategory(QLatin1String("Entertainment"), 1, true, false, QLatin1String(""));
    DatabaseConnector::createCategory(QLatin1String("Salary"), 1, false, true, QLatin1String(""));
    DatabaseConnector::createCategory(QLatin1String("Scholarship"), 1, false, true, QLatin1String(""));

    return QSqlError();
}
