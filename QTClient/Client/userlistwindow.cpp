#include "userlistwindow.h"
#include "ui_userlistwindow.h"
#include "utils.h"
#include "constants.h"
#include "../../Common/uri.h"
#include <assert.h>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

UserListWindow::UserListWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserListWindow),
    _manager(new QNetworkAccessManager()),
    _tableWidget(ui->usersTable)
{
    ui->setupUi(this);

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

UserListWindow::~UserListWindow()
{
    delete ui;
}
