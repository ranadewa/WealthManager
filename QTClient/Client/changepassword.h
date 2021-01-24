#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include "../../Common/DTO/user.h"

namespace Ui {
class ChangePassword;
}

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
     ChangePassword(QWidget *parent = nullptr,  QNetworkAccessManager* manager = nullptr, User user = {});
    ~ChangePassword();

private slots:

    void on_buttonBox_accepted();

private:
    Ui::ChangePassword *ui;

     QNetworkAccessManager* _manager;
     User _user;
};

#endif // CHANGEPASSWORD_H
