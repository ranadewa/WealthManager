#include "httpserver.h"
#include "uri.h"

void display_json(
	json::value const& jvalue,
	utility::string_t const& prefix)
{
	std::wcout << prefix << jvalue.serialize() << std::endl;
}


int main () {

	HTTPServer server(URI::host);

	server.registerEndpoint(methods::PUT, URI::authenticate, [](web::http::http_request request) {
		wcout << "Authenticate invoked" << endl;
		request.reply(status_codes::OK);
	});


	try
	{
		server.start();

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