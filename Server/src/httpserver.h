#pragma once

#include<cpprest/http_listener.h>
#include <cpprest/json.h>

#include<iostream>
#include <functional>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#define TRACE(msg)            std::wcout << msg

class HTTPServer
{
	typedef std::function<void(web::http::http_request)> Action;

public:
	HTTPServer(utility::string_t baseURI);

	void registerEndpoint(method method, utility::string_t path, Action action);

	void start();

private:
	utility::string_t _baseURI;
	http_listener _listner;
	std::unordered_map<utility::string_t, Action> _routes;
};
