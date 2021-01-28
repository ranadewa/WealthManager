#include "utils.h"
#include "constants.h"
#include "../../Common/uri.h"
#include <QUrlQuery>

namespace Util {
    QNetworkRequest createRequest(QString uri, QUrlQuery* query)
    {
        QString host(URI::host.c_str());
        QString overview = host + uri;

        QNetworkRequest request;
        QUrl url = QUrl(overview);

        if(query)
        {
            url.setQuery(*query);
        }

        request.setUrl(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        return request;
    }

    QString wToQ(std::wstring const& string)
    {
        return QString::fromWCharArray(string.c_str());
    }

}

