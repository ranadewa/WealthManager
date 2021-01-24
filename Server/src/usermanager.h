#pragma once

#include <string>
#include <unordered_map>

using namespace std;

struct User
{
    string _name;
    string _id;
    string _password;
    bool _isAdmin;
};

class UserManager
{
public:
    UserManager();
    string authenticate(string const& userName, string const& password);
    bool updatePassword(string const& userId, string const& oldPassword, string const& newPassword);
    bool addUser(string const& userName, string const& password);
    bool deleteUser(string const& userName, string const& password);

private:
    unordered_map<string, User> _users;
    unordered_map<string, string> _idLookup;
};