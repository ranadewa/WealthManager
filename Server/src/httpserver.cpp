#include "httpserver.h"

HTTPServer::HTTPServer(utility::string_t baseURI) : _baseURI(baseURI), _listner(_baseURI)
{
	_listner.support([this](web::http::http_request request) {
		auto path = request.method() + request.request_uri().to_string();
		wcout << "path: " << path << endl;

		if (_routes.find(path) != _routes.end())
		{
			_routes.at(path)(request);
		}
	});
}

void HTTPServer::registerEndpoint(method method, utility::string_t path, Action action)
{
	_routes.insert({ method + path, action });
}

void HTTPServer::start()
{
	_listner.open().then([this]() { std::wcout << "Server started on: " << _baseURI << std::endl;  }).wait();
}