#include "utils.h"
#include "constants.h"

namespace Util {
    QNetworkRequest createRequest(char const* uri)
    {
        QString host(URI::host);
        QString overview = host + QString(uri);

        QNetworkRequest request;
        request.setUrl(QUrl(overview));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        return request;
    }
}

