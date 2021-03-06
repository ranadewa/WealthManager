#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <memory>
#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include "../../Common/DTO/user.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    User _user;

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginWindow *ui;
    std::unique_ptr<QNetworkAccessManager> _networkManager;

};

#endif // LOGINWINDOW_H
