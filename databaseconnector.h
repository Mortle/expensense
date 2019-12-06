#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QtSql>

class DatabaseConnector
{
public:
    DatabaseConnector();

    QVariant create_user(const QString &username, const QString &password);
    QVariant create_category(const QString &name, int user_id, bool expense, bool income, const QString &description);
    void update_category(int id, const QString &name, const QString &description);
    void remove_category(int id);
    QVariant create_operation(int category_id, int value, int user_id, const QString &description);
    void update_operation(int id, int category_id, int value, const QString &description);
    void remove_operation(int id);
};

#endif // DATABASECONNECTOR_H
