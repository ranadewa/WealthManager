#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "changepassword.h"
#include "addnewuser.h"
#include "userlistwindow.h"

MainWindow::MainWindow(QWidget *parent,  User user)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _manager(new QNetworkAccessManager(parent))
    , _user(user)
{
    ui->setupUi(this);
    _overView.reset(new Overview(ui->tableWidget, _manager.get()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_changePassword_clicked()
{
    ChangePassword window(this, _manager.get(), _user);
    window.exec();
}

void MainWindow::on_addUser_clicked()
{
    AddNewUser window(this, _manager.get());
    window.exec();
}

void MainWindow::on_getUsers_clicked()
{
    UserListWindow window(this, _manager.get());
    window.exec();
}
