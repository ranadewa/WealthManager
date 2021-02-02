#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "changepassword.h"
#include "addnewuser.h"
#include "utils.h"
#include "constants.h"
#include "../../Common/uri.h"
#include <assert.h>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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
    QNetworkRequest request = Util::createRequest(URI::user.c_str());

    QObject::connect(_manager.get(),
                     &QNetworkAccessManager::finished,
                     this,
                     [=](QNetworkReply *reply) {
               if (reply->error()) {
                   qDebug() << reply->errorString();
                   return;
               }

               auto responsedata = reply->readAll();
               qDebug() << QString{responsedata};
               QJsonArray users = QJsonDocument::fromJson(responsedata).array();

               if(!users.isEmpty())
               {
                   auto i =0;
                   auto iter = users.begin();
                   auto end = users.end();

                   ui->usersTable->setRowCount(users.size());
                   while(iter != end)
                   {
                       auto jsonObject = (*iter).toObject();
                       ui->usersTable->setColumnCount(jsonObject.size());

                       ui->usersTable->setItem(i, 0, new QTableWidgetItem(jsonObject["id"].toString()));
                        ui->usersTable->setItem(i, 1, new QTableWidgetItem(jsonObject["name"].toString()));
                        ui->usersTable->setItem(i, 2, new QTableWidgetItem(jsonObject["isAdmin"].toBool()));
                        ++iter;
                        ++i;
                   }

               }

           }
       );


    _manager->get(request);
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

void MainWindow::on_addBank_clicked()
{
    _investmentTab->addInvestment();
}

void MainWindow::on_addShares_clicked()
{
    _investmentTab->addInvestment();
}

void MainWindow::on_addProperty_clicked()
{
    _investmentTab->addInvestment();
}

void MainWindow::on_addOthers_clicked()
{
    _investmentTab->addInvestment();
}
