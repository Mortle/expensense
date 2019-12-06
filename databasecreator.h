#ifndef DATABASECREATOR_H
#define DATABASECREATOR_H

#include <QtSql>

class DatabaseCreator
{
private:
    QLatin1String createUsersTableSql;
    QLatin1String createCategoriesTableSql;
    QLatin1String createOperationsTableSql;
public:
    DatabaseCreator();

    QSqlError initializeDatabase();
};

#endif // DATABASECREATOR_H
