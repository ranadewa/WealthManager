#include "changepassword.h"
#include "ui_changepassword.h"
#include "../../Common/uri.h"
#include "utils.h"
#include <QNetworkReply>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>


ChangePassword::ChangePassword(QWidget *parent,  QNetworkAccessManager* manager, User user) :
    QDialog(parent),
    ui(new Ui::ChangePassword),
    _manager(manager),
    _user(user)
{
    ui->setupUi(this);
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_buttonBox_accepted()
{
    auto newPassword  = ui->newPassword->text();
    auto confirmPassword = ui->confirmPassword->text();
    auto password = ui->oldPassword->text();

    if(newPassword.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) // Validate
        return ;

    auto request = Util::createRequest(URI::changepassword.c_str());

    QObject::connect(_manager,
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
    data["id"] = QString(_user._id.c_str());
    data["newPassword"] = newPassword;
    data["oldPassword"] = password;
    QJsonDocument doc = QJsonDocument::fromVariant(data);

    _manager->post(request, doc.toJson());
}
