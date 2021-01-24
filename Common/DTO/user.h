#ifndef USER_H
#define USER_H

#include<string>
struct User
{
    std::string _name;
    std::string _id;
    std::string _password;
    bool _isAdmin;
};
#endif // USER_H