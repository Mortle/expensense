#include "databasecreator.h"
#include "databaseconnector.cpp"

DatabaseCreator::DatabaseCreator()
{
    createUsersTableSql = QLatin1String(R"(
        create table users(id integer primary key, username varchar, password varchar, created_at varchar)
        )");

    createOperationsTableSql = QLatin1String(R"(
        create table operations(id integer primary key, category_id integer, user_id integer,
                                value int, description varchar, created_at varchar)
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

    DatabaseConnector database;

    database.createUser(QLatin1String("Dmitry Osipov"), QLatin1String("AMz6J34Mg&zJ9@MC"));
    database.createUser(QLatin1String("Alexander Vinogradov"), QLatin1String("boomer"));
    database.createUser(QLatin1String("Valery Duleba"), QLatin1String("e3LQ6T&Eh6kp-J&6"));

    database.createCategory(QLatin1String("Other"), 0, true, false, QLatin1String(""));
    database.createCategory(QLatin1String("Cafe"), 0, true, false, QLatin1String(""));
    database.createCategory(QLatin1String("Rent"), 0, true, false, QLatin1String(""));
    database.createCategory(QLatin1String("Food"), 0, true, false, QLatin1String(""));
    database.createCategory(QLatin1String("Entertainment"), 0, true, false, QLatin1String(""));
    database.createCategory(QLatin1String("Salary"), 0, false, true, QLatin1String(""));
    database.createCategory(QLatin1String("Scholarship"), 0, false, true, QLatin1String(""));

    return QSqlError();
}
