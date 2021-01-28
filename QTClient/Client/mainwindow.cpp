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
    _overViewTab.reset(new Overview(ui->tableWidget));

    InvestmentTables table;
    table._map.insert({Wealth::InvestmentType::BANK, ui->banksTable});
    table._map.insert({Wealth::InvestmentType::SHARE_MARKET, ui->capitalMarketsTable});
    table._map.insert({Wealth::InvestmentType::PROPERTY, ui->propertyTable});
    table._map.insert({Wealth::InvestmentType::OTHER, ui->otherInvTable});

    _investmentTab.reset(new Investments( table, _user));
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
    UserListWindow window(this);
    window.exec();
}

void MainWindow::on_mainTabs_currentChanged(int index)
{
    switch ((TabIndex)index) {
        case TabIndex::OVERVIEW :
        break;
        case TabIndex::BUDGET :
        break;
        case TabIndex::BALANCE_SHEET :
        break;
        case TabIndex::INVESTMENTS :
            _investmentTab->onSelected();
        break;
        case TabIndex::SYSTEM :
        break;
    default:
        break;
    }
}
