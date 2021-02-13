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

		std::thread t(&HTTPServer::start, &server);  // Start server in a separate thread

		while (true)  // Server is designed to spin endlessly
		{
			this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		t.join();
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error "<< ex.what() << std::endl;
	}

    return 0;
}