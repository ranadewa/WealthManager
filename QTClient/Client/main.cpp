#include "mainwindow.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow login;

    if(login.exec())
    {
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
