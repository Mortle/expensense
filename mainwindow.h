#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void refreshData();

private slots:
    void on_loginPushButton_clicked();

    void logoutPushButton_clicked();

    void on_registerPushButton_clicked();

    void on_createOperationPushButton_clicked();

    void on_updateOperationPushButton_clicked();

    void on_deleteOperationPushButton_clicked();

    void on_createExpCategoryPushButton_clicked();

    void on_removeExpCategoryPushButton_clicked();

    void on_createIncCategoryPushButton_clicked();

    void on_removeIncCategoryPushButton_clicked();

private:
    Ui::MainWindow *ui;
    int currentUserId;
};
#endif // MAINWINDOW_H
