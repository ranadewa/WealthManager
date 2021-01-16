#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <QWidget>
#include <QtWidgets/QTableWidget>
#include <QtNetwork/QNetworkAccessManager>

class Overview : public QObject
{
public:
    Overview(QTableWidget* table, QNetworkAccessManager* manager);

private:
    QNetworkAccessManager* _networkManager;
    QTableWidget* _tableWidget;
    QString _name;
    long _cash = 0;
    long _investment= 0;
    long _liabilities= 0;
    long _netWorth = 0;
};

#endif // OVERVIEW_H
