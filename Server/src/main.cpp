#include<cpprest/http_listener.h>
#include<iostream>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#define TRACE(msg)            std::wcout << msg

int main () {

	const utility::string_t url = U("http://1.0.0.127/restdemo");

    http_listener listner(url);

    listner.support(methods::GET,  [](http_request request) {
        request.reply(200);
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