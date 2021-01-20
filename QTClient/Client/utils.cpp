#include "utils.h"
#include "constants.h"
#include "../../Common/uri.h"

namespace Util {
    QNetworkRequest createRequest(QString uri)
    {
        QString host(wToQ(URI::host));
        QString overview = host + uri;

        QNetworkRequest request;
        request.setUrl(QUrl(overview));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        return request;
    }

    QString wToQ(std::wstring const& string)
    {
        return QString::fromWCharArray(string.c_str());
    }

}

