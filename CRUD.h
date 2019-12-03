#ifndef CRUD_H
#define CRUD_H

#include <QtSql>

QVariant create_user(const QString &email, const QString &username,
                  const QString &password) {
    const auto sql = QLatin1String(R"(
        insert into users(email, username, password, created_at) values(?, ?, ?, ?)
        )");
    QSqlQuery q;
    q.prepare(sql);
    q.addBindValue(email);
    q.addBindValue(username);
    q.addBindValue(password);
    q.addBindValue(QDateTime::currentDateTime().toString());
    q.exec();
    return q.lastInsertId();
}

QVariant create_category(const QString &name, int user_id,
                      bool expense, bool income, const QString &description) {
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

QVariant create_operation(int category_id, int value,
                       int user_id, const QString &description) {
    const auto sql = QLatin1String(R"(
        insert into operations(category_id, user_id, value, description, created_at) values(?, ?, ?, ?, ?)
        )");
    QSqlQuery q;
    q.prepare(sql);
    q.addBindValue(category_id);
    q.addBindValue(user_id);
    q.addBindValue(value);
    q.addBindValue(description);
    q.addBindValue(QDateTime::currentDateTime().toString());
    q.exec();
    return q.lastInsertId();
}

#endif // CRUD_H
