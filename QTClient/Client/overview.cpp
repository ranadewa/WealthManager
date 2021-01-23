#include "overview.h"
#include "utils.h"
#include "constants.h"
#include "../../Common/uri.h"
#include <assert.h>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>


Overview::Overview(QTableWidget* table, QNetworkAccessManager* manager) : _networkManager(manager), _tableWidget(table)
{
    assert(_tableWidget != nullptr);

    QNetworkRequest request = Util::createRequest(URI::overview.c_str());

    QObject::connect(manager,
                     &QNetworkAccessManager::finished,
                     this,
                     [=](QNetworkReply *reply) {
               if (reply->error()) {
                   qDebug() << reply->errorString();
                   return;
               }

               QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

               if(!doc.isNull() && doc.isObject())
               {
                   QJsonObject obj = doc.object();

                   _name = obj["name"].toString();
                   _cash = obj["cash"].toInt();
                   _investment = obj["investment"].toInt();
                   _liabilities = obj["liabilities"].toInt();
                   _netWorth = obj["netWorth"].toInt();



                   _tableWidget->setItem(0, 1, new QTableWidgetItem(_name));
                   _tableWidget->setItem(1, 1, new QTableWidgetItem(QString::number(_cash)));
                   _tableWidget->setItem(2, 1, new QTableWidgetItem(QString::number(_investment)));
                   _tableWidget->setItem(3, 1, new QTableWidgetItem(QString::number(_liabilities)));
                   _tableWidget->setItem(4, 1, new QTableWidgetItem(QString::number(_netWorth)));
               }

           }
       );


    manager->get(request);
}
