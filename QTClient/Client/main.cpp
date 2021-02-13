#include "mainwindow.h"
#include "loginwindow.h"
#include "utils.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Util::CurrencyMapper::_currencyMapper.insert(QString("USD"), Wealth::Currency::USD);
    Util::CurrencyMapper::_currencyMapper.insert(QString("SGD"), Wealth::Currency::SGD);
    Util::CurrencyMapper::_currencyMapper.insert(QString("LKR"), Wealth::Currency::LKR);

    LoginWindow login;

    if(login.exec())
    {
        User user = login._user;

        MainWindow w(nullptr, user);
        w.show();
        return a.exec();
    }

    return 0;
}
