#ifndef URI_H
#define URI_H

#include<string>
// #include <codecvt>
 // #include <locale>

namespace URI {
    const std::wstring host = L"http://localhost:1081";
    const std::wstring overview = L"/overview";
    const std::wstring user = L"/user";
    const std::wstring authenticate = L"/user/authenticate";
    const std::wstring changepassword = L"/user/changepassword";
}
#endif // URI_H