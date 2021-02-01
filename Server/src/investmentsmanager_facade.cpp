#include "investmentsmanager_facade.h"
#include "uri.h"

namespace Facade {
    InvestmentManagerFacade::InvestmentManagerFacade(HTTPServer& server, Wealth::InvestmentManager& manager) : _manager(manager)
    {
        server.registerEndpoint(methods::GET, URI::investments, std::bind(&InvestmentManagerFacade::getInvestments, this, std::placeholders::_1));
    }

    void InvestmentManagerFacade::getInvestments(HttpRequest request)
    {
        std::cout << " body " << request.body() << std::endl;
		request
			.extract_utf8string()
			.then([request, this](pplx::task < std::string > task) {
			try
			{

				std::string const& jvalue = task.get();
				std::cout << "Body: " << jvalue << endl;

				std::string id;

				if (_manager.hasInvestment(id))
				{
					auto investments = _manager.getInvestments(id);
				}
				else
				{
					// TODO send error
				}
			}
			catch (http_exception const& e)
			{
				request.reply(status_codes::InternalError, U("Internal Server Error"));
				std::cout << e.what() << endl;
			}
		})
			.wait();

        request.reply(status_codes::OK, "Everything fine");
    }
}