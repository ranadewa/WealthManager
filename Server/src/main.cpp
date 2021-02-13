#include <thread>
#include "httpserver.h"
#include "uri.h"
#include "usermanager_facade.h"
#include "investmentsmanager_facade.h"
#include "currencyconverter.h"

void display_json(
	json::value const& jvalue,
	utility::string_t const& prefix)
{
	std::wcout << prefix << jvalue.serialize() << std::endl;
}


int main () {

	HTTPServer server(URI::host);
	UserManager userManager(make_unique<UserFileRepository>());
	UserManagerFacade userManagerFacade(server, userManager);

	CurrencyConverter converter(server);

	Wealth::InvestmentManager investmentManager(make_unique<Wealth::InvestmentsRepository>(userManager.getUserIds()), converter);
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