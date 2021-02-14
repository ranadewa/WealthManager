#include "investmentstab.h"
#include "utils.h"
#include "../../Common/uri.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "newinvestment.h"



int Investments::addValuesToTable(QTableWidget* table, QJsonArray array, int rowIndex)
{

    auto iter = array.begin();
    auto end = array.end();

    while (iter != end)
    {
        auto account = (*iter).toObject();

        QString valueList;
        auto values = account[Wealth::Holding::VALUES_KEY.c_str()];
        if (values.isArray()) {
            auto valueArray = values.toArray();
            auto valueIter = valueArray.begin();
            auto valueIterEnd = valueArray.end();

            while (valueIter != valueIterEnd)
            {
                 auto value = (*valueIter).toObject();


                 auto price = value[Wealth::Amount::VALUE_KEY.c_str()].toInt();
                 auto currency = static_cast<Wealth::Currency>(value[Wealth::Amount::CURRENCY_KEY.c_str()].toInt());

                 auto currencyString = Util::CurrencyMapper::getKey(currency);

                 valueList +=  QString::number(price) + " " + currencyString + " ";

                 ++valueIter;
            }

           table->setItem(rowIndex, 1, new QTableWidgetItem(account[Wealth::Holding::NAME_KEY.c_str()].toString()));
           table->setItem(rowIndex, 2, new QTableWidgetItem(valueList));
        }

        ++iter;
        ++rowIndex;
    }

    return rowIndex;
}

void Investments::addToBankTable(QJsonObject const& investment)
{

    auto table = _tables._map.at(Wealth::InvestmentType::BANK);
    table->clearContents();

    auto cash = investment[Wealth::Bank::CASHACCOUNT_KEY.c_str()];
    auto fixedDeposit = investment[Wealth::Bank::FIXEDDEPOSIT_KEY.c_str()];

    table->setRowCount(cash.toArray().size() + fixedDeposit.toArray().size());
    int rowIndex = 0;
    if (cash.isArray()) {
        table->setItem(0, 0, new QTableWidgetItem(Wealth::Bank::CASHACCOUNT_KEY.c_str()));
        rowIndex = addValuesToTable(table, cash.toArray());
    }


    if (fixedDeposit.isArray()) {
        table->setItem(rowIndex, 0, new QTableWidgetItem(Wealth::Bank::FIXEDDEPOSIT_KEY.c_str()));
        addValuesToTable(table, fixedDeposit.toArray(), rowIndex);
    }

}

void Investments::addToShareMaketTable(QJsonObject const& investment)
{
    auto table = _tables._map.at(Wealth::InvestmentType::SHARE_MARKET);
    table->clearContents();

    auto equities = investment[Wealth::ShareMarket::EQUITIES_KEY.c_str()];
    auto bonds = investment[Wealth::ShareMarket::BONDS_KEY.c_str()];
    auto reits = investment[Wealth::ShareMarket::REITS_KEY.c_str()];

    table->setRowCount(equities.toArray().size() + bonds.toArray().size() + reits.toArray().size());
    int rowIndex = 0;
    if (equities.isArray()) {
        table->setItem(0, 0, new QTableWidgetItem(Wealth::ShareMarket::EQUITIES_KEY.c_str()));
        rowIndex = addValuesToTable(table, equities.toArray());
    }


    if (bonds.isArray()) {
        table->setItem(rowIndex, 0, new QTableWidgetItem(Wealth::ShareMarket::BONDS_KEY.c_str()));
        rowIndex = addValuesToTable(table, bonds.toArray(), rowIndex);
    }

    if (reits.isArray()) {
        table->setItem(rowIndex, 0, new QTableWidgetItem(Wealth::ShareMarket::REITS_KEY.c_str()));
        addValuesToTable(table, reits.toArray(), rowIndex);
    }
}


void Investments::addToPropertiesTable(QJsonObject const& investment)
{
    auto table = _tables._map.at(Wealth::InvestmentType::PROPERTY);
    table->clearContents();

    auto commercial = investment[Wealth::Property::COMMERCIAL_KEY.c_str()];
    auto residential = investment[Wealth::Property::RESIDENTIAL_KEY.c_str()];
    auto lands = investment[Wealth::Property::LAND_KEY.c_str()];

    table->setRowCount(commercial.toArray().size() + residential.toArray().size() + lands.toArray().size());
    int rowIndex = 0;
    if (commercial.isArray()) {
        table->setItem(0, 0, new QTableWidgetItem(Wealth::Property::COMMERCIAL_KEY.c_str()));
        rowIndex = addValuesToTable(table, commercial.toArray());
    }


    if (residential.isArray()) {
        table->setItem(rowIndex, 0, new QTableWidgetItem(Wealth::Property::RESIDENTIAL_KEY.c_str()));
        rowIndex = addValuesToTable(table, residential.toArray(), rowIndex);
    }

    if (lands.isArray()) {
        table->setItem(rowIndex, 0, new QTableWidgetItem(Wealth::Property::LAND_KEY.c_str()));
        addValuesToTable(table, lands.toArray(), rowIndex);
    }
}
void Investments::addToOtherTable(QJsonObject const& investment)
{
    auto table = _tables._map.at(Wealth::InvestmentType::OTHER);
    table->clearContents();

    auto other = investment[Wealth::OtherInvestments::OTHER_KEY.c_str()];

    table->setRowCount(other.toArray().size());
    if (other.isArray()) {
        table->setItem(0, 0, new QTableWidgetItem(Wealth::OtherInvestments::OTHER_KEY.c_str()));
        addValuesToTable(table, other.toArray());
    }
}

Investments::Investments(InvestmentTables tables,  User& user) : _networkManager(new QNetworkAccessManager()),
    _tables(tables),
    _user(user)
{

}

void Investments::onSelected()
{
    QUrlQuery query;
    query.addQueryItem(QString("user"), QString(_user._id.c_str()));

    QNetworkRequest request = Util::createRequest(URI::investments.c_str(), &query);

    QNetworkReply *reply = _networkManager->get(request);

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
               QJsonArray investments = QJsonDocument::fromJson(responsedata).array();

               if(!investments.empty())
               {
                   auto i =0;
                   auto iter = investments.begin();
                   auto end = investments.end();

                   while(iter != end)
                   {
                       auto investment = (*iter).toObject();

                       auto type = static_cast<Wealth::InvestmentType>(investment[Wealth::Investments::TYPE_KEY.c_str()].toInt());
                       switch (type) {
                           case Wealth::InvestmentType::BANK:
                           {
                               addToBankTable(investment);
                               break;
                           }
                           case Wealth::InvestmentType::SHARE_MARKET:
                           {
                               addToShareMaketTable(investment);
                               break;
                           }
                           case Wealth::InvestmentType::PROPERTY:
                           {
                               addToPropertiesTable(investment);
                               break;
                           }
                           case Wealth::InvestmentType::OTHER:
                           {
                               addToOtherTable(investment);
                               break;
                           }
                       default:
                           break;
                       }

                        ++iter;
                        ++i;
                   }
               }

               reply->deleteLater();
           }
       );
}

void Investments::addInvestment()
{
    NewInvestment window(nullptr, _user);
    if(window.exec())
    {
        QUrlQuery query;
        query.addQueryItem(QString("user"), QString(_user._id.c_str()));

        QNetworkRequest request = Util::createRequest(URI::investments.c_str(), &query);

         QNetworkReply *reply = _networkManager->post(request, window._investment.dump().c_str());

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
                    reply->deleteLater();
                }
            );
    }

}
