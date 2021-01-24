#ifndef ADDNEWUSER_H
#define ADDNEWUSER_H

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>


namespace Ui {
class AddNewUser;
}

class AddNewUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewUser(QWidget *parent = nullptr, QNetworkAccessManager* manager = nullptr);
    ~AddNewUser();

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::AddNewUser *ui;
    QNetworkAccessManager* _manager;
};

#endif // ADDNEWUSER_H
