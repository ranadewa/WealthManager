#include "investmentsmanager_facade.h"
#include "uri.h"

namespace Facade {
    InvestmentManagerFacade::InvestmentManagerFacade(HTTPServer& server, Wealth::InvestmentManager& manager) : _manager(manager)
    {
        server.registerEndpoint(methods::GET, URI::investments, std::bind(&InvestmentManagerFacade::getInvestments, this, std::placeholders::_1));
        server.registerEndpoint(methods::POST, URI::investments, std::bind(&InvestmentManagerFacade::postInvestments, this, std::placeholders::_1));
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

    void InvestmentManagerFacade::postInvestments(HttpRequest request)
    {
        request
            .extract_json()
            .then([this, request](pplx::task<json::value> task) {
            try
            {

                auto const& jvalue = task.get();

                if (!jvalue.is_null())
                {
                    
                }
            }
            catch (http_exception const& e)
            {
                request.reply(status_codes::InternalError, U("Internal Server Error"));
                std::cout << e.what() << endl;
            }
        })
            .wait();
    }
}