#include<cpprest/http_listener.h>
#include <cpprest/json.h>

#include<iostream>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#define TRACE(msg)            std::wcout << msg

void handle_get(http_request request)
{
	TRACE(L"\nhandle GET\n");

	request.reply(status_codes::OK);
}

void display_json(
	json::value const& jvalue,
	utility::string_t const& prefix)
{
	std::wcout << prefix << jvalue.serialize() << std::endl;
}

int main () {

	const utility::string_t uri = U("http://localhost:1081/overview");

    http_listener listner(uri);

    listner.support(methods::GET,  [](http_request request) {
		std::cout << "get invoked" << std::endl;
		auto result = web::json::value::object();

		result[U("name")] = web::json::value(U("John Doe"));
		result[U("cash")] = web::json::value(2000);

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