#ifndef UTILS_H
#define UTILS_H

#include "../../Common/DTO/investments.h"
#include<QNetworkRequest>
#include <QUrlQuery>

namespace Util {
    QNetworkRequest createRequest(QString uri, QUrlQuery* query = nullptr);
    QString wToQ(std::wstring const& string);

    struct CurrencyMapper {
       static QString getKey(Wealth::Currency currency);
       static QMap<QString, Wealth::Currency> _currencyMapper;
    };

}
#endif // UTILS_H
