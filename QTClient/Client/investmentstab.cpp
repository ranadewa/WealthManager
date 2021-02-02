#include "investmentstab.h"
#include "utils.h"
#include "../../Common/uri.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "newinvestment.h"

Investments::Investments(InvestmentTables tables,  User& user) : _networkManager(new QNetworkAccessManager()),
    _tables(std::move(tables)),
    _user(user)
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
               QJsonArray investments = QJsonDocument::fromJson(responsedata).array();

               if(!investments.empty())
               {

               }

           }
       );
}

void Investments::onSelected()
{
    QUrlQuery query;
    query.addQueryItem(QString("user"), QString(_user._id.c_str()));

    QNetworkRequest request = Util::createRequest(URI::investments.c_str(), &query);

    _networkManager->get(request);
}

void Investments::addInvestment()
{
    NewInvestment window;
    window.exec();
}
