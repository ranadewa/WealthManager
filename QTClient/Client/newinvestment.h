#ifndef NEWINVESTMENT_H
#define NEWINVESTMENT_H

#include <QDialog>
#include <QMap>
#include "../../Common/DTO/investments.h"

namespace Ui {
class NewInvestment;
}

class NewInvestment : public QDialog
{
    Q_OBJECT

public:
    explicit NewInvestment(QWidget *parent = nullptr);
    ~NewInvestment();

private slots:
    void on_addInvestment_clicked();

    void on_mainType_activated(int index);

private:
    Ui::NewInvestment *ui;
    QMap<QString, Wealth::InvestmentType> _typeMapper;
};

#endif // NEWINVESTMENT_H
