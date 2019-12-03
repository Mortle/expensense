#ifndef CRUD_H
#define CRUD_H

#include <QtSql>

QVariant create_user(const QString &email, const QString &username, const QString &password) {
    //TODO: reject if username already exists
    //TODO: email validation
    //TODO: username, password validatios
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

QVariant create_category(const QString &name, int user_id, bool expense, bool income, const QString &description) {
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

void update_category(int id, const QString &name, const QString &description) {
    QSqlQuery q;
    q.prepare("UPDATE categories SET name = ?, description = ? WHERE id = ?");
    q.addBindValue(name);
    q.addBindValue(description);
    q.addBindValue(id);
    q.exec();
}

void remove_category(int id) {
    //TODO: remove all operations with category_id === id
    //TODO: QMessageBox warning: all operations will be deleted
    QSqlQuery q;
    q.prepare("DELETE FROM categories WHERE id = ?");
    q.addBindValue(id);
    q.exec();
}

QVariant create_operation(int category_id, int value, int user_id, const QString &description) {
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

void update_operation(int id, int category_id, int value, const QString &description) {
    //TODO: new categody_id exists? validation
    QSqlQuery q;
    q.prepare("UPDATE operations SET category_id = ?, description= ?, value = ? WHERE id = ?");
    q.addBindValue(category_id);
    q.addBindValue(description);
    q.addBindValue(value);
    q.addBindValue(id);
    q.exec();
}

void remove_operation(int id) {
    QSqlQuery q;
    q.prepare("DELETE FROM operations WHERE id = ?");
    q.addBindValue(id);
    q.exec();
}

#endif // CRUD_H
