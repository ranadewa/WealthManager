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
	HTTPServer(string baseURI);

	void registerEndpoint(method method, string path, Action action);

	void start();

private:
	string _baseURI;
	http_listener _listner;
	std::unordered_map<string, Action> _routes;
};
