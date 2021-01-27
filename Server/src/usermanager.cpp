#include "usermanager.h"
#include <algorithm>
#include <iterator>

UserManager::UserManager(IUserRepository::IUserRepositoryPtr repository) : _repository(std::move(repository))
{
    vector<User> userList = _repository->getUsers();

    for (auto & user : userList)
    {
        _idLookup.insert({ user._name, user._id });
        _users.insert({ user._id, std::move(user) });
    }
}

User UserManager::authenticate(string const& userName, string const& password)
{
    User result{};

    if (_idLookup.find(userName) != _idLookup.end())
    {
        auto id = _idLookup.at(userName);

        if (_users.find(id) != _users.end())
        {
            auto storedPassword = _users.at(id)._password; // To do decrypt password

            if (storedPassword.compare(password) == 0) // passoword match
            {
                result = _users.at(id);
            }
        }
    }

    return result;
}

bool UserManager::updatePassword(string const& id, string const& oldPassword, string const& newPassword)
{

    if (_users.find(id) != _users.end())
    {
        auto storedPassword = _users.at(id)._password; // To do decrypt password

        if (storedPassword.compare(oldPassword) == 0) // passoword match
        {
            if (_repository->updateUsers(getUsers()))
            {
                _users.at(id)._password = newPassword;
            }
        }
    }

    return false;
}

bool UserManager::addUser(User&& user, string& error)
{

    if (_idLookup.find(user._name) != _idLookup.end()) // User exists
    {
        error = "User already exists";
        return false;
    }

    user._id = to_string(_idLookup.size() + 1); // Give user next available id

    if (_repository->addUser(user))
    {
        _idLookup.insert({ user._name ,  user._id });
        _users.insert({ user._id, std::move(user) }); // To do encrypt password
    }
    else
    {
        error = "Failed to add user to repository";
        return false;
    }


    return true;;
}

bool UserManager::deleteUser(string const& userName, string const& password)
{
    return false;
}

vector<User> UserManager::getUsers()
{
    vector<User> users;

    transform(_users.begin(), _users.end(), std::back_inserter(users), [this](std::pair<string, User> const& pair) {
        return pair.second;
    });

    return users;
}
