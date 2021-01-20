#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "constants.h"
#include "utils.h"
#include "../../Common/uri.h"
#include <QNetworkReply>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>


LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow),
    _networkManager(new QNetworkAccessManager(parent))
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_clicked()
{
    auto name  = ui->userName->text();
    auto password = ui->password->text();

    if(name.isEmpty() || password.isEmpty()) // Validate
        return ;

    auto request = Util::createRequest(Util::wToQ(URI::authenticate));

    QObject::connect(_networkManager.get(),
                     &QNetworkAccessManager::finished,
                     this,
                     [=](QNetworkReply *reply) {
               if (reply->error()) {
                   qDebug() << reply->errorString();
                   return;
               }
               else
               {
                   QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

                   if(!statusCode.isNull() && statusCode.toInt() == 200)
                   {
                       accept();
                   }

                   // TODO handle reject
               }
           }
       );


    QVariantMap data;
    data["name"] = name;
    data["password"] = password;
    QJsonDocument doc = QJsonDocument::fromVariant(data);

    _networkManager->put(request, doc.toJson());
}
