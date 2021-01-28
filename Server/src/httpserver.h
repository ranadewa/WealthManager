#pragma once

#include<cpprest/http_listener.h>
#include <cpprest/json.h>

#include<iostream>
#include <functional>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#ifdef _WIN32
#define TRACE(msg)            std::wcout << msg << std::endl;
#else
#define TRACE(msg)            std::cout << msg << std::endl;
#endif // _WIN32

typedef web::http::http_request HttpRequest;

class HTTPServer
{
	typedef std::function<void(web::http::http_request)> Action;

public:
	HTTPServer(string baseURI);

	void registerEndpoint(method method, string path, Action action);

	void start();

private:
	utility::string_t _baseURI;
	http_listener _listner;
	std::unordered_map<utility::string_t, Action> _routes;
};
