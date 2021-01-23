#ifndef URI_H
#define URI_H

#include<string>
// #include <codecvt>
 // #include <locale>

namespace URI {
    const std::string host = "http://localhost:1081";
    const std::string overview = "/overview";
    const std::string user = "/user";
    const std::string authenticate = "/user/authenticate";
    const std::string changepassword = "/user/changepassword";
}
#endif // URI_H