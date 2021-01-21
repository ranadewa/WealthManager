#pragma once

#include <string>

using namespace std;

class UserManager
{
public:
    string authentiate(string const& userName, string const& password);
    bool updatePassword(string const& userId, string const& oldPassword, string const& newPassword);
    bool addUser(string const& userName, string const& password);
    bool deleteUser(string const& userName, string const& password);

private:

};