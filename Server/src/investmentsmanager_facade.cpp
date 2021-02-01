#include "investmentsmanager_facade.h"
#include "uri.h"

namespace Facade {
    InvestmentManagerFacade::InvestmentManagerFacade(HTTPServer& server, Wealth::InvestmentManager& manager) : _manager(manager)
    {
        server.registerEndpoint(methods::GET, URI::investments, std::bind(&InvestmentManagerFacade::getInvestments, this, std::placeholders::_1));
    }

    void InvestmentManagerFacade::getInvestments(HttpRequest request)
    {
		auto query = request.request_uri().query();
		auto id = utility::conversions::to_utf8string(query.substr(5, query.size()));

        if (_manager.hasInvestment(id))
        {
            auto investments = _manager.getInvestments(id);
            request.reply(status_codes::OK, investments.to_json().dump());
        }
        else
        {
            request.reply(status_codes::OK);
        }
    }
}