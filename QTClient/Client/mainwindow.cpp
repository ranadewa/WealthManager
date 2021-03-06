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
#include "utils.h"
#include "errordialog.h"
#include "confirmationdialog.h"

MainWindow::MainWindow(QWidget *parent,  User user)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _manager(new QNetworkAccessManager(parent))
    , _user(user)
{
    ui->setupUi(this);
    _overViewTab.reset(new Overview(ui->tableWidget, _user));

    InvestmentTables table;
    table._map.insert({Wealth::InvestmentType::BANK, ui->banksTable});
    table._map.insert({Wealth::InvestmentType::SHARE_MARKET, ui->capitalMarketsTable});
    table._map.insert({Wealth::InvestmentType::PROPERTY, ui->propertyTable});
    table._map.insert({Wealth::InvestmentType::OTHER, ui->otherInvTable});

    _investmentTab.reset(new Investments( table, _user));

    ui->sourceCurrency->addItem(Util::CurrencyMapper::getKey(Wealth::Currency::USD));
    ui->destinationCurrency->addItem(Util::CurrencyMapper::getKey(Wealth::Currency::SGD));
    ui->destinationCurrency->addItem(Util::CurrencyMapper::getKey(Wealth::Currency::LKR));

    on_tabWidget_tabBarClicked(0);
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



    QNetworkReply *reply = _manager->get(request);
    QObject::connect(reply,
                     &QIODevice::readyRead,
                     this,
                     [=]() {
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

                    ui->usersTable->clearContents();
                   ui->usersTable->setRowCount(users.size());
                   while(iter != end)
                   {
                       auto jsonObject = (*iter).toObject();
                       ui->usersTable->setColumnCount(jsonObject.size());

                       ui->usersTable->setItem(i, 0, new QTableWidgetItem(jsonObject["id"].toString()));
                       ui->usersTable->setItem(i, 1, new QTableWidgetItem(jsonObject["name"].toString()));
                        ++iter;
                        ++i;
                   }
               }

           }
       );
}

void MainWindow::on_addNew_clicked()
{
    _investmentTab->addInvestment();
}

void MainWindow::on_updateButton_clicked()
{
    if(ui->conversionRate->text().size() == 0)
    {
        ErrorDialog window;
        window.exec();

        return;
    }

    auto desitnationCurrency  = Util::CurrencyMapper::_currencyMapper.value(ui->destinationCurrency->currentText());
    auto value = ui->conversionRate->text().toDouble();

    auto request = Util::createRequest(URI::currency.c_str());

    QVariantMap data;
    data["currency"] = (int)desitnationCurrency;
    data["value"] = value;

    QJsonDocument doc = QJsonDocument::fromVariant(data);

    QNetworkReply *reply =_manager->post(request, doc.toJson());

    QObject::connect(reply,
                     &QIODevice::readyRead,
                     this,
                     [=]() {
               if (reply->error()) {
                   qDebug() << reply->errorString();
                   return;
               }
               else
               {
                   QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

                   if(!statusCode.isNull() && statusCode.toInt() == 200)
                   {
                   }

                   // TODO handle reject
               }
           }
       );

    ConfirmationDialog window(this);
    window.exec();
}


void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    switch ((TabIndex)index) {
        case TabIndex::OVERVIEW :
         _overViewTab->onSelected();
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

void MainWindow::on_refreshButton_clicked()
{
    _investmentTab->onSelected();
}
