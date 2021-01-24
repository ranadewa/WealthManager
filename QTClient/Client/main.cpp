#include "mainwindow.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
