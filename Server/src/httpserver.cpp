#include "httpserver.h"

HTTPServer::HTTPServer(string baseURI) : _baseURI(baseURI), _listner(utility::conversions::to_string_t(_baseURI))
{
	_listner.support([this](web::http::http_request request) {
		auto path = utility::conversions::utf16_to_utf8(request.method() + request.request_uri().to_string());
		cout << "path: " << path << endl;

		if (_routes.find(path) != _routes.end())
		{
			_routes.at(path)(request);
		}
	});
}

void HTTPServer::registerEndpoint(method method, string path, Action action)
{
	_routes.insert({ (utility::conversions::utf16_to_utf8(method) + path), action });
}

void HTTPServer::start()
{
	_listner.open().then([this]() { std::cout << "Server started on: " << _baseURI << std::endl;  }).wait();
}