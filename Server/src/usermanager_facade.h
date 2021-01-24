#pragma once

#include <string>
#include "httpserver.h"
#include "usermanager.h"

using namespace std;

class UserManagerFacade
{
    typedef web::http::http_request HttpRequest;
public:
    UserManagerFacade(HTTPServer &server, UserManager& manager);

private:
    void onAuthRequest(HttpRequest request);
    void onPasswordChange(HttpRequest request);
    void add(HttpRequest request);
    void deleteUser(HttpRequest request);
    void getUserList(HttpRequest request);

    UserManager& _manager;

};