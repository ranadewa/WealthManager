#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "changepassword.h"

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
    ChangePassword changePasswordUI(this, _manager.get(), _user);
    changePasswordUI.exec();
}

void MainWindow::on_addUser_clicked()
{

}

void MainWindow::on_getUsers_clicked()
{

}
