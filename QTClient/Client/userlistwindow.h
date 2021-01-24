#ifndef USERLISTWINDOW_H
#define USERLISTWINDOW_H

#include <QDialog>
#include <QtWidgets/QTableWidget>
#include <QtNetwork/QNetworkAccessManager>

namespace Ui {
class UserListWindow;
}

class UserListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserListWindow(QWidget *parent = nullptr, QNetworkAccessManager* manager =nullptr);
    ~UserListWindow();

private:
    Ui::UserListWindow *ui;
    QNetworkAccessManager* _manager;
    QTableWidget* _tableWidget;
};

#endif // USERLISTWINDOW_H
