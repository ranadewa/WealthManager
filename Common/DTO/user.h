#pragma once

#include<string>
#include"nlohmann/json.hpp"

struct User
{
    User(std::string name, std::string id, std::string password,  bool isAdmin) : 
        _name(name), _id(id), _password(password), _isAdmin(isAdmin) {}
    User() {};

    User(const nlohmann::json& j) {

        if (has(NAME_KEY, j))
            j.at(NAME_KEY).get_to(_name);

        if(has(ID_KEY, j))
            j.at(ID_KEY).get_to(_id);

        if (has(PASSWORD_KEY, j))
            j.at(PASSWORD_KEY).get_to(_password);

        if (has(ADMIN_KEY, j))
            j.at(ADMIN_KEY).get_to(_isAdmin);
    }

    std::string _name;
    std::string _id;
    std::string _password;
    bool _isAdmin = false;

    nlohmann::json to_json() const{
        auto j = nlohmann::json{ {NAME_KEY, _name}, {ID_KEY, _id}, { PASSWORD_KEY, _password}, {ADMIN_KEY, _isAdmin} };
        return j;
    }

private:
    std::string NAME_KEY{ "name" };
    std::string ID_KEY{ "id" };
    std::string PASSWORD_KEY{ "password" };
    std::string ADMIN_KEY{ "isAdmin" };

    bool has(std::string key, nlohmann::json const& j) {
        return j.find(key) != j.end();
    }
};
