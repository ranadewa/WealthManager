#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <QWidget>
#include <QtWidgets/QTableWidget>

class Overview
{
public:
    Overview(QTableWidget* table = nullptr);

private:
    QTableWidget* _tableWidget;
    std::string _name;
    long _cash = 0;
    long _investment= 0;
    long _liabilities= 0;
    long _netWorth = 0;
};

#endif // OVERVIEW_H
