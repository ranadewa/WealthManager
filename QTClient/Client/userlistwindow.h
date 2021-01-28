#ifndef USERLISTWINDOW_H
#define USERLISTWINDOW_H

#include <memory>
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
     UserListWindow(QWidget *parent = nullptr);
    ~UserListWindow();

private:
    Ui::UserListWindow *ui;
    std::unique_ptr<QNetworkAccessManager> _manager;
    QTableWidget* _tableWidget;
};

#endif // USERLISTWINDOW_H
