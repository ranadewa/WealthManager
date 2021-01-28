#ifndef UTILS_H
#define UTILS_H

#include<QNetworkRequest>
#include <QUrlQuery>

namespace Util {
    QNetworkRequest createRequest(QString uri, QUrlQuery* query = nullptr);
    QString wToQ(std::wstring const& string);
}
#endif // UTILS_H
