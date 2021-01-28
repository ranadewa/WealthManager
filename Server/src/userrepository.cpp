#include "userrepository.h"
#include <sstream>

UserFileRepository::UserFileRepository() : _fileName("managing_users.txt")
{
    ifstream checkFile(_fileName, ifstream::in);

    if (!checkFile.good()) // file doesnt exist
    {
        ofstream file(_fileName, ofstream::out); // create

        if (file.is_open())
        {
            writeUser(file, User{ "admin", "1", "123", true });
        }
            
    }
}

vector<User> UserFileRepository::getUsers()
{
    string line;
    vector<User> users;
    ifstream file(_fileName, ifstream::in);

    while (getline(file, line))
    {
        stringstream stream(line);
        User user;
        stream >> user._name  >> user._id >> user._password >> user._isAdmin;
        users.push_back(user);
    }

    return users;
}

bool UserFileRepository::addUser(User const& user)
{
    ofstream file(_fileName, ofstream::app); // append
    writeUser(file, user);
    return true;
}

bool UserFileRepository::updateUsers(vector<User> const& users)
{
    ofstream file(_fileName, ofstream::trunc); // over write

    for (auto const& user : users)
    {
        writeUser(file, user);
    }

    return true;
}

void UserFileRepository::writeUser(ofstream & file, User const& user)
{
    file << user._name << " " << user._id << " " << user._password << " " << user._isAdmin << std::endl;
}
