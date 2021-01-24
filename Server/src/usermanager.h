#pragma once

#include <string>
#include <unordered_map>
#include <user.h>

using namespace std;

class UserManager
{
public:
    UserManager();
    User authenticate(string const& userName, string const& password);
    bool updatePassword(string const& id, string const& oldPassword, string const& newPassword);
    bool addUser(User&& user, string & error);
    bool deleteUser(string const& userName, string const& password);

private:
    unordered_map<string, User> _users;
    unordered_map<string, string> _idLookup;
};