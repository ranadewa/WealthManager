#include "investmentsmanager.h"

namespace Wealth {

    Investments InvestmentManager::getInvestments(std::string userID)
    {
        return _investments.at(userID);
    }

    bool InvestmentManager::hasInvestment(std::string userID)
    {
        return _investments.find(userID) == _investments.end() ;
    }

}