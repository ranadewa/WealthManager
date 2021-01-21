#include "httpserver.h"
#include "uri.h"
#include "usermanager.h"
#include "usermanager_facade.h"

void display_json(
	json::value const& jvalue,
	utility::string_t const& prefix)
{
	std::wcout << prefix << jvalue.serialize() << std::endl;
}


int main () {

	HTTPServer server(URI::host);
	UserManager userManager;
	UserManagerFacade userManagerFacade(server, userManager);

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