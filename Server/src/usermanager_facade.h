#pragma once

#include <string>
#include "httpserver.h"
#include "usermanager.h"

using namespace std;

class UserManagerFacade
{

public:
    UserManagerFacade(HTTPServer &server, UserManager& manager);

private:
    void onAuthRequest(HttpRequest request);
    void onPasswordChange(HttpRequest request);
    void add(HttpRequest request);
    void deleteUser(HttpRequest request);
    void getUserList(HttpRequest request);
    void parse(HttpRequest request, function<void(json::value)> out);

    UserManager& _manager;

};