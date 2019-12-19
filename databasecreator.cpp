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

    DatabaseConnector::createUser(QLatin1String("Alexander Vinogradov"), QLatin1String("test"));

    DatabaseConnector::createCategory(QLatin1String("Savings"), 1, true, false, QLatin1String("Saving up money for Tesla Cybertruck"));
    DatabaseConnector::createCategory(QLatin1String("Debt"), 1, true, false, QLatin1String("Lannisters always pay their debts"));
    DatabaseConnector::createCategory(QLatin1String("Food"), 1, true, false, QLatin1String("Any nutritious substance that I eat or drink in order to maintain life and growth."));
    DatabaseConnector::createCategory(QLatin1String("Rent"), 1, true, false, QLatin1String("Monthly rental fee"));
    DatabaseConnector::createCategory(QLatin1String("Salary"), 1, false, true, QLatin1String("Programmer's monthly salary"));
    DatabaseConnector::createCategory(QLatin1String("Scholarship"), 1, false, true, QLatin1String("University pays me pennies for my existence"));

    DatabaseConnector::createOperation(QLatin1String("Savings"), 10.0, 1, QLatin1String(""));
    DatabaseConnector::createOperation(QLatin1String("Savings"), 15.0, 1, QLatin1String(""));
    DatabaseConnector::createOperation(QLatin1String("Salary"), 250.0, 1, QLatin1String(""));
    DatabaseConnector::createOperation(QLatin1String("Salary"), 300.0, 1, QLatin1String(""));
    DatabaseConnector::createOperation(QLatin1String("Scholarship"), 45.0, 1, QLatin1String(""));
    DatabaseConnector::createOperation(QLatin1String("Scholarship"), 50.0, 1, QLatin1String(""));
    DatabaseConnector::createOperation(QLatin1String("Food"), 14.44, 1, QLatin1String(""));
    DatabaseConnector::createOperation(QLatin1String("Food"), 12.33, 1, QLatin1String(""));
    DatabaseConnector::createOperation(QLatin1String("Food"), 1.01, 1, QLatin1String(""));
    DatabaseConnector::createOperation(QLatin1String("Debt"), 100.0, 1, QLatin1String(""));
    DatabaseConnector::createOperation(QLatin1String("Rent"), 150.0, 1, QLatin1String(""));

    return QSqlError();
}
