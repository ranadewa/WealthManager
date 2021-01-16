#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _manager(new QNetworkAccessManager(parent))
{
    ui->setupUi(this);
    _overView.reset(new Overview(ui->tableWidget, _manager.get()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

