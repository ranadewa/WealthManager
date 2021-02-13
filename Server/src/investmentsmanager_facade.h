#pragma once
#include "httpserver.h"
#include "investmentsmanager.h"

using namespace std;
namespace Facade {
	class InvestmentManagerFacade
	{
	public:
		InvestmentManagerFacade(HTTPServer& server, Wealth::InvestmentManager& manager);

	private:
		Wealth::InvestmentManager& _manager;

		void getInvestmentOverview(HttpRequest request);
		void getInvestments(HttpRequest request);
		void postInvestments(HttpRequest request);
	};
}