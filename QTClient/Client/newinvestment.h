#ifndef NEWINVESTMENT_H
#define NEWINVESTMENT_H

#include <QDialog>
#include <QMap>
#include <QNetworkAccessManager>
#include "../../Common/DTO/investments.h"
#include "../../Common/DTO/nlohmann/json.hpp"
#include "../../Common/DTO/user.h"

namespace Ui {
class NewInvestment;
}

class NewInvestment : public QDialog
{
    Q_OBJECT

public:
    explicit NewInvestment(QWidget *parent = nullptr, User user = {});
    ~NewInvestment();

     nlohmann::json _investment;
private slots:
    void on_addInvestment_clicked();

    void on_mainType_activated(int index);

private:
    Ui::NewInvestment *ui;
    QMap<QString, Wealth::InvestmentType> _typeMapper;

    User _user;
    void updateCategory();
    void updateCurrency();
    std::string getType(Wealth::InvestmentType type);
};

#endif // NEWINVESTMENT_H
