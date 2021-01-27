#pragma once
#include "user.h"
#include <vector>
#include <memory>
#include <fstream>

using namespace std;

class IUserRepository {
public:
    virtual vector<User> getUsers() = 0;
    virtual bool addUser(User const& user) = 0;
    virtual bool updateUsers(vector<User> const& users) = 0;

    typedef unique_ptr<IUserRepository> IUserRepositoryPtr;
};

class UserFileRepository : public IUserRepository
{
public:
    UserFileRepository();
    vector<User> getUsers() override;
    bool addUser(User const& user) override;
    bool updateUsers(vector<User> const& users) override;

private:
    void writeUser(ofstream & file, User const& user);
    const string _fileName;
};