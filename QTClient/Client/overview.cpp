#include "overview.h"
#include "utils.h"
#include "constants.h"
#include "../../Common/uri.h"
#include <assert.h>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>


Overview::Overview(QTableWidget* table,  User& user) :
    _networkManager(new QNetworkAccessManager()),
    _user(user),
    _tableWidget(table)
{

}

void Overview::onSelected()
{
    QObject::connect(_networkManager.get(),
                     &QNetworkAccessManager::finished,
                     this,
                     [=](QNetworkReply *reply) {
               if (reply->error()) {
                   qDebug() << reply->errorString();
                   return;
               }

               auto responsedata = reply->readAll();
               qDebug() << QString{responsedata};

               QJsonDocument doc = QJsonDocument::fromJson(responsedata);

               if(!doc.isNull() && doc.isObject())
               {
                   _tableWidget->clearContents();
                   _tableWidget->setRowCount(6);

                   QJsonObject obj = doc.object();
                   auto usd = QString(" USD");
                   _tableWidget->setItem(0, 0, new QTableWidgetItem("User Name"));
                   _tableWidget->setItem(0, 1, new QTableWidgetItem(_user._name.c_str()));
                   _tableWidget->setItem(1, 0, new QTableWidgetItem("Bank accounts"));
                   _tableWidget->setItem(1, 1, new QTableWidgetItem(QString::number(obj[Wealth::Overview::BANK_KEY.c_str()].toDouble()) + usd));
                   _tableWidget->setItem(2, 0, new QTableWidgetItem("Share Market"));
                   _tableWidget->setItem(2, 1, new QTableWidgetItem(QString::number(obj[Wealth::Overview::SHARES_KEY.c_str()].toDouble())+ usd));
                   _tableWidget->setItem(3, 0, new QTableWidgetItem("Properties"));
                   _tableWidget->setItem(3, 1, new QTableWidgetItem(QString::number(obj[Wealth::Overview::PROPERTIES_KEY.c_str()].toDouble())+ usd));
                   _tableWidget->setItem(4, 0, new QTableWidgetItem("Others"));
                   _tableWidget->setItem(4, 1, new QTableWidgetItem(QString::number(obj[Wealth::Overview::OTHERS_KEY.c_str()].toDouble())+ usd));
                   _tableWidget->setItem(5, 0, new QTableWidgetItem("Net Worth"));
                   _tableWidget->setItem(5, 1, new QTableWidgetItem(QString::number(obj[Wealth::Overview::NETWORTH_KEY.c_str()].toDouble())+ usd));
               }

           }
       );

    QUrlQuery query;
    query.addQueryItem(QString("user"), QString(_user._id.c_str()));

    QNetworkRequest request = Util::createRequest(URI::overview.c_str(), &query);

    _networkManager->get(request);
}
