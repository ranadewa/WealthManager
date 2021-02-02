#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include "overview.h"
#include "investmentstab.h"
#include "../../Common/DTO/user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class TabIndex {
    OVERVIEW = 0,
    BUDGET,
    BALANCE_SHEET,
    INVESTMENTS,
    SYSTEM
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, User user = {});
    ~MainWindow();

private slots:


    void on_changePassword_clicked();

    void on_addUser_clicked();

    void on_getUsers_clicked();

    void on_mainTabs_currentChanged(int index);

    void on_addNew_clicked();

private:

    Ui::MainWindow *ui;
    std::unique_ptr<QNetworkAccessManager> _manager;
    User _user;

    std::unique_ptr<Overview> _overViewTab;
    std::unique_ptr<Investments> _investmentTab;

};
#endif // MAINWINDOW_H
