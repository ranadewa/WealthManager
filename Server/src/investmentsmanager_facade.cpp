#include "investmentsmanager_facade.h"
#include "uri.h"

namespace Facade {
    InvestmentManagerFacade::InvestmentManagerFacade(HTTPServer& server, Wealth::InvestmentManager& manager) : _manager(manager)
    {
        server.registerEndpoint(methods::GET, URI::investments, std::bind(&InvestmentManagerFacade::getInvestments, this, std::placeholders::_1));
    }

    void InvestmentManagerFacade::getInvestments(HttpRequest request)
    {
        std::cout << request.body() << std::endl;
        request.reply(status_codes::OK, "Everything fine");
    }
}