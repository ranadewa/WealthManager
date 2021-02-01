#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "userrepository.h"

using namespace std;

class UserManager
{
public:
    UserManager(IUserRepository::IUserRepositoryPtr repository);
    bool authenticate(User & user);
    bool updatePassword(User& user, string const& newPassword);
    bool addUser(User&& user, string & error);
    bool deleteUser(string const& userName, string const& password);
    vector<User> getUsers();

private:
    unordered_map<string, User> _users;
    unordered_map<string, string> _idLookup;
    IUserRepository::IUserRepositoryPtr _repository;
};