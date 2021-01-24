#include "usermanager.h"

UserManager::UserManager()
{
    User user{ "admin", "1", "123", true };  // To do encrypt password

    _idLookup.insert({ user._name, user._id });
    _users.insert({ user._id, std::move(user) });
}

string UserManager::authenticate(string const& userName, string const& password)
{
    string result{};

    if (_idLookup.find(userName) != _idLookup.end())
    {
        auto id = _idLookup.at(userName);

        if (_users.find(id) != _users.end())
        {
            auto storedPassword = _users.at(id)._password; // To do decrypt password

            if (storedPassword.compare(password) == 0) // passoword match
            {
                result = id;
            }
        }
    }

    return result;
}

bool UserManager::updatePassword(string const& userId, string const& oldPassword, string const& newPassword)
{
    return false;
}

bool UserManager::addUser(string const& userName, string const& password)
{
    return false;
}

bool UserManager::deleteUser(string const& userName, string const& password)
{
    return false;
}
