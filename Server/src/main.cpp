#include<cpprest/http_listener.h>
#include <cpprest/json.h>

#include<iostream>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#define TRACE(msg)            std::wcout << msg

int main () {

	const utility::string_t uri = U("http://localhost:1081/overview");

    http_listener listner(uri);

    listner.support(methods::GET,  [](http_request request) {
		std::cout << "get invoked" << std::endl;
		auto result = web::json::value::object();

		result[U("name")] = web::json::value(U("John Doe"));
		result[U("cash")] = web::json::value(2000);
		result[U("investment")] = web::json::value(3000);
		result[U("liabilities")] = web::json::value(1000);
		result[U("netWorth")] = web::json::value(10000);

        request.reply(200, result);
    });

	try
	{
		listner.open().then([&listner]() {TRACE(L"\nstarting to listen\n"); }).wait();
		while (true)
		{

		}
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error "<< ex.what() << std::endl;
	}

    return 0;
}