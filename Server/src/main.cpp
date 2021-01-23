#include "httpserver.h"
#include "uri.h"
#include "usermanager.h"
#include "usermanager_facade.h"


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