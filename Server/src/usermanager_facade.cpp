#include "usermanager_facade.h"
#include <functional>
#include "uri.h"

UserManagerFacade::UserManagerFacade(HTTPServer& server, UserManager& manager)
{
    server.registerEndpoint(methods::PUT, URI::authenticate, std::bind(&UserManagerFacade::onAuthRequest, this, std::placeholders::_1));
    server.registerEndpoint(methods::POST, URI::changepassword, std::bind(&UserManagerFacade::onPasswordChange, this, std::placeholders::_1));
    server.registerEndpoint(methods::POST, URI::user, std::bind(&UserManagerFacade::add, this, std::placeholders::_1));
    server.registerEndpoint(methods::DEL, URI::user, std::bind(&UserManagerFacade::deleteUser, this, std::placeholders::_1));
    server.registerEndpoint(methods::GET, URI::user, std::bind(&UserManagerFacade::getUserList, this, std::placeholders::_1));
}

void UserManagerFacade::onAuthRequest(HttpRequest request)
{
    cout << "on Auth request received." << endl;


}

void UserManagerFacade::onPasswordChange(HttpRequest request)
{
    cout << "onPasswordChange." << endl;
}

void UserManagerFacade::add(HttpRequest request)
{
    cout << "add." << endl;
}

void UserManagerFacade::deleteUser(HttpRequest request)
{
    cout << "deleteUser." << endl;
}

void UserManagerFacade::getUserList(HttpRequest request)
{
    cout << "getUserList." << endl;
}
