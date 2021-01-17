#include<cpprest/http_listener.h>
#include <cpprest/json.h>

#include<iostream>
#include <functional>

using namespace std;
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
	std::cout << prefix << jvalue.serialize() << std::endl;
}

void handle_request(
	http_request request,
	std::function<void(json::value const&, json::value&)> action)
{
	auto answer = json::value::object();

	request
		.extract_json()
		.then([&answer, &action](pplx::task<json::value> task) {
		try
		{
			auto const& jvalue = task.get();
			display_json(jvalue, L"R: ");

			if (!jvalue.is_null())
			{
				action(jvalue, answer);
			}
		}
		catch (http_exception const& e)
		{
			std::cout << e.what() << endl;
		}
	})
		.wait();


	display_json(answer, L"S: ");

	request.reply(status_codes::OK, answer);
}

int main () {

	const utility::string_t uri = U("http://localhost:1081/overview"); 
	const utility::string_t authUri = U("http://localhost:1081/authenticate");

    http_listener listner(uri);
	http_listener authListner(authUri);

	authListner.support(methods::PUT, [](http_request request) {

		request
			.extract_json()
			.then([request](pplx::task<json::value> task) {
			try
			{

				auto const& jvalue = task.get();
				display_json(jvalue, L"R: ");

				if (!jvalue.is_null())
				{
					auto name = jvalue.at(U("name")).as_string();
					auto password = jvalue.at(U("password")).as_string();

					if (name.compare(U("abc")) == 0 && password.compare(U("123")) == 0)
					{
						request.reply(status_codes::OK);
					}
					else
					{
						request.reply(status_codes::BadRequest, U("Invalid username or password"));
					}
				}
			}
			catch (http_exception const& e)
			{
				request.reply(status_codes::InternalError, U("Internal Server Error"));
				std::cout << e.what() << endl;
			}
		})
			.wait();
	});

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
		authListner.open().wait();

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