#ifndef UTILS_H
#define UTILS_H

#include<QNetworkRequest>

namespace Util {
    QNetworkRequest createRequest(char const* uri);
}
#endif // UTILS_H
