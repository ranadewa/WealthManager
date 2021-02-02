#ifndef INVESTMENTS_H
#define INVESTMENTS_H

#include <QObject>
#include <QtWidgets/QTableWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <unordered_map>
#include <memory>
#include "../../Common/DTO/investments.h"
#include "../../Common/DTO/user.h"

struct InvestmentTables {
    std::unordered_map<Wealth::InvestmentType, QTableWidget*> _map;
};

class Investments : public QObject
{
public:
    Investments(InvestmentTables tables,  User& _user);
    void onSelected();
    void addInvestment();

private:
    std::unique_ptr<QNetworkAccessManager> _networkManager;
    InvestmentTables _tables;
    User& _user;
};

#endif // INVESTMENTS_H
