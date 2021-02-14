#include "httpserver.h"

HTTPServer::HTTPServer(string baseURI) : _baseURI(utility::conversions::to_string_t(baseURI)), _listner(_baseURI)
{
	_listner.support([this](web::http::http_request request) {

		auto path = request.method() + request.request_uri().path();
		TRACE(path);

		std::lock_guard lock(_mutex);
		if (_routes.find(path) != _routes.end())
		{
			_routes.at(path)(request);
		}
	});
}

void HTTPServer::registerEndpoint(method method, string path, Action action)
{
	std::lock_guard lock(_mutex);
	_routes.insert({ method + utility::conversions::to_string_t(path), action });
}

void HTTPServer::start()
{
	_listner.open().then([this]() { std::cout << "Server started on: " << _baseURI << std::endl;  }).wait();
	_listner.open().then([this]() { TRACE("Server started on: "); TRACE(_baseURI)  }).wait();
}