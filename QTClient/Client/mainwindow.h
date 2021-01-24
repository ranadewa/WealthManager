#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <overview.h>
#include "../../Common/DTO/user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, User user = {});
    ~MainWindow();

private slots:


    void on_changePassword_clicked();

    void on_addUser_clicked();

    void on_getUsers_clicked();

private:

    Ui::MainWindow *ui;
    std::unique_ptr<QNetworkAccessManager> _manager;
    User _user;

    std::unique_ptr<Overview> _overView;
};
#endif // MAINWINDOW_H
