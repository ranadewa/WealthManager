#include "newinvestment.h"
#include "ui_newinvestment.h"
#include <QStringList>
#include "utils.h"

NewInvestment::NewInvestment(QWidget *parent, User user) :
    QDialog(parent),
    ui(new Ui::NewInvestment),
    _user(user)
{
    ui->setupUi(this);
    _typeMapper.insert(QString("Bank"), Wealth::InvestmentType::BANK);
    _typeMapper.insert(QString("Share Market"), Wealth::InvestmentType::SHARE_MARKET);
    _typeMapper.insert(QString("Property"), Wealth::InvestmentType::PROPERTY);
    _typeMapper.insert(QString("Other"), Wealth::InvestmentType::OTHER);


    ui->mainType->addItems(QStringList(_typeMapper.keys()));
    updateCategory();
    updateCurrency();
}

NewInvestment::~NewInvestment()
{
    delete ui;
}

void NewInvestment::on_addInvestment_clicked()
{
    _investment = nlohmann::json({
                                     {Wealth::Investments::TYPE_KEY.c_str(), _typeMapper.value(ui->mainType->currentText())},
                                     {Wealth::Investments::CATEGORY_KEY.c_str(), ui->category->currentText().toStdString()},
                                     {Wealth::Holding::NAME_KEY.c_str(), ui->name->text().toStdString()},
                                     {Wealth::Amount::VALUE_KEY.c_str(), ui->amount->text().toDouble()},
                                     {Wealth::Amount::CURRENCY_KEY.c_str(), Util::CurrencyMapper::_currencyMapper.value(ui->currency->currentText())},
                                     {"userid", _user._id}
                                 });
    accept();
}


void NewInvestment::on_mainType_activated(int index)
{
    updateCategory();
}

void NewInvestment::updateCategory()
{
    auto type = _typeMapper.value(ui->mainType->currentText());
    ui->category->clear();
    switch (type) {
        case Wealth::InvestmentType::BANK:
        ui->category->addItems(QStringList({QString(Wealth::Bank::CASHACCOUNT_KEY.c_str()), QString(Wealth::Bank::FIXEDDEPOSIT_KEY.c_str())}));
        break;
        case Wealth::InvestmentType::SHARE_MARKET:
        ui->category->addItems(QStringList({QString(Wealth::ShareMarket::EQUITIES_KEY.c_str()),
                                            QString(Wealth::ShareMarket::BONDS_KEY.c_str()), QString(Wealth::ShareMarket::REITS_KEY.c_str())}));
        break;
        case Wealth::InvestmentType::PROPERTY:
        ui->category->addItems(QStringList({QString(Wealth::Property::RESIDENTIAL_KEY.c_str()),
                                            QString(Wealth::Property::COMMERCIAL_KEY.c_str()), QString(Wealth::Property::LAND_KEY.c_str())}));
        break;
        case Wealth::InvestmentType::OTHER:
        break;
    }
}

void NewInvestment::updateCurrency()
{
    ui->currency->addItems(QStringList(Util::CurrencyMapper::_currencyMapper.keys()));
}

std::string NewInvestment::getType(Wealth::InvestmentType type)
{
    switch (type) {
        case Wealth::InvestmentType::BANK:
        return "bank";
        case Wealth::InvestmentType::SHARE_MARKET:
        return "shareMarket";
        case Wealth::InvestmentType::PROPERTY:
        return "property";
        case Wealth::InvestmentType::OTHER:
        return "other";
    }
}

