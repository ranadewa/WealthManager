#include "newinvestment.h"
#include "ui_newinvestment.h"
#include <QStringList>

NewInvestment::NewInvestment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewInvestment)
{
    ui->setupUi(this);
    _typeMapper.insert(QString("Bank"), Wealth::InvestmentType::BANK);
    _typeMapper.insert(QString("Share Market"), Wealth::InvestmentType::SHARE_MARKET);
    _typeMapper.insert(QString("Property"), Wealth::InvestmentType::PROPERTY);
    _typeMapper.insert(QString("Other"), Wealth::InvestmentType::OTHER);

    ui->mainType->addItems(QStringList(_typeMapper.keys()));
}

NewInvestment::~NewInvestment()
{
    delete ui;
}

void NewInvestment::on_addInvestment_clicked()
{

}


void NewInvestment::on_mainType_activated(int index)
{
    auto type = _typeMapper.value(ui->mainType->currentText());
    ui->category->clear();
    switch (type) {
        case Wealth::InvestmentType::BANK:
        ui->category->addItems(QStringList({QString("cash"), QString("Fixed Deposit")}));
        break;
        case Wealth::InvestmentType::SHARE_MARKET:
        ui->category->addItems(QStringList({QString("equity"), QString("bond"), QString("reit")}));
        break;
        case Wealth::InvestmentType::PROPERTY:
        ui->category->addItems(QStringList({QString("residential"), QString("commercial"), QString("land")}));
        break;
        case Wealth::InvestmentType::OTHER:
        break;
    }
}
