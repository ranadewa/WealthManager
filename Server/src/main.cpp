#include <thread>
#include "httpserver.h"
#include "uri.h"
#include "usermanager_facade.h"
#include "investmentsmanager_facade.h"


int main () {

	HTTPServer server(URI::host);
	UserManager userManager(make_unique<UserFileRepository>());
	UserManagerFacade userManagerFacade(server, userManager);

	Wealth::InvestmentManager investmentManager;
	Facade::InvestmentManagerFacade investmentMangerFacade(server, investmentManager);

	try
	{
		server.start();

		while (true)
		{
			this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error "<< ex.what() << std::endl;
	}

    return 0;
}