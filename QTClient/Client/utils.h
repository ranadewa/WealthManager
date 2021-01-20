#ifndef UTILS_H
#define UTILS_H

#include<QNetworkRequest>

namespace Util {
    QNetworkRequest createRequest(QString uri);
    QString wToQ(std::wstring const& string);
}
#endif // UTILS_H
