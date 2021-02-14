#include "addnewuser.h"
#include "ui_addnewuser.h"
#include "utils.h"
#include "../../Common/uri.h"
#include <QNetworkReply>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>
#include "errordialog.h"
#include "confirmationdialog.h"

AddNewUser::AddNewUser(QWidget *parent, QNetworkAccessManager* manager) :
    QDialog(parent),
    ui(new Ui::AddNewUser),
    _manager(manager)
{
    ui->setupUi(this);
}

AddNewUser::~AddNewUser()
{
    delete ui;
}

void AddNewUser::on_ok_clicked()
{
    auto userName  = ui->userName->text();
    auto password = ui->password->text();
    auto isAdmin = ui->admin->isChecked();


    if(userName.isEmpty() || password.isEmpty()) // Validate
    {
        ErrorDialog window;
        window.exec();

        return;
    }

    auto request = Util::createRequest(URI::user.c_str());

    QObject::connect(_manager,
                     &QNetworkAccessManager::finished,
                     this,
                     [=](QNetworkReply *reply) {
               if (reply->error()) {
                   qDebug() << reply->errorString();
                   ErrorDialog window;
                   window.exec();
                   return;
               }
               else
               {
                   QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

                   if(!statusCode.isNull() && statusCode.toInt() == 200)
                   {
                       accept();
                   }

               }
           }
       );


    QVariantMap data;
    data["name"] = userName;
    data["password"] = password;
    data["isAdmin"] = isAdmin;
    QJsonDocument doc = QJsonDocument::fromVariant(data);

    _manager->post(request, doc.toJson());
}

void AddNewUser::on_cancel_clicked()
{
    accept();
}
