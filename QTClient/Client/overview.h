#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <memory>
#include <QWidget>
#include <QtWidgets/QTableWidget>
#include <QtNetwork/QNetworkAccessManager>
#include "../../Common/DTO/user.h"

class Overview : public QObject
{
public:
    Overview(QTableWidget* table,  User& user);
    void onSelected();

private:
    std::unique_ptr<QNetworkAccessManager> _networkManager;
    User& _user;
    QTableWidget* _tableWidget;
};

#endif // OVERVIEW_H
