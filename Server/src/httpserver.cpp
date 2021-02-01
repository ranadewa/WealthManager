#include "httpserver.h"

HTTPServer::HTTPServer(string baseURI) : _baseURI(utility::conversions::to_string_t(baseURI)), _listner(_baseURI)
{
	_listner.support([this](web::http::http_request request) {

		auto path = request.method() + request.request_uri().path();
		TRACE(path);

		if (_routes.find(path) != _routes.end())
		{
			_routes.at(path)(request);
		}
	});
}

void HTTPServer::registerEndpoint(method method, string path, Action action)
{
	_routes.insert({ method + utility::conversions::to_string_t(path), action });
}

void HTTPServer::start()
{
	_listner.open().then([this]() { TRACE("Server started on: "); TRACE(_baseURI)  }).wait();
}