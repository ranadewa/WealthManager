#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _overView.reset(new Overview(ui->tableWidget));
}

MainWindow::~MainWindow()
{
    delete ui;
}

